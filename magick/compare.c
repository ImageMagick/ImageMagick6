/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%               CCCC   OOO   M   M  PPPP    AAA   RRRR    EEEEE               %
%              C      O   O  MM MM  P   P  A   A  R   R   E                   %
%              C      O   O  M M M  PPPP   AAAAA  RRRR    EEE                 %
%              C      O   O  M   M  P      A   A  R R     E                   %
%               CCCC   OOO   M   M  P      A   A  R  R    EEEEE               %
%                                                                             %
%                                                                             %
%                      MagickCore Image Comparison Methods                    %
%                                                                             %
%                              Software Design                                %
%                                  Cristy                                     %
%                               December 2003                                 %
%                                                                             %
%                                                                             %
%  Copyright 1999 ImageMagick Studio LLC, a non-profit organization dedicated %
%  to making software imaging solutions freely available.                     %
%                                                                             %
%  You may not use this file except in compliance with the License.  You may  %
%  obtain a copy of the License at                                            %
%                                                                             %
%    https://imagemagick.org/script/license.php                               %
%                                                                             %
%  Unless required by applicable law or agreed to in writing, software        %
%  distributed under the License is distributed on an "AS IS" BASIS,          %
%  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   %
%  See the License for the specific language governing permissions and        %
%  limitations under the License.                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/artifact.h"
#include "magick/attribute.h"
#include "magick/cache-view.h"
#include "magick/channel.h"
#include "magick/client.h"
#include "magick/color.h"
#include "magick/color-private.h"
#include "magick/colorspace.h"
#include "magick/colorspace-private.h"
#include "magick/compare.h"
#include "magick/composite-private.h"
#include "magick/constitute.h"
#include "magick/exception-private.h"
#include "magick/geometry.h"
#include "magick/image-private.h"
#include "magick/list.h"
#include "magick/log.h"
#include "magick/memory_.h"
#include "magick/monitor.h"
#include "magick/monitor-private.h"
#include "magick/option.h"
#include "magick/pixel-private.h"
#include "magick/property.h"
#include "magick/resource_.h"
#include "magick/statistic-private.h"
#include "magick/string_.h"
#include "magick/string-private.h"
#include "magick/statistic.h"
#include "magick/thread-private.h"
#include "magick/transform.h"
#include "magick/utility.h"
#include "magick/version.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C o m p a r e I m a g e C h a n n e l s                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CompareImageChannels() compares one or more image channels of an image
%  to a reconstructed image and returns the difference image.
%
%  The format of the CompareImageChannels method is:
%
%      Image *CompareImageChannels(const Image *image,
%        const Image *reconstruct_image,const ChannelType channel,
%        const MetricType metric,double *distortion,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o reconstruct_image: the reconstruct image.
%
%    o channel: the channel.
%
%    o metric: the metric.
%
%    o distortion: the computed distortion between the images.
%
%    o exception: return any errors or warnings in this structure.
%
*/

MagickExport Image *CompareImages(Image *image,const Image *reconstruct_image,
  const MetricType metric,double *distortion,ExceptionInfo *exception)
{
  Image
    *highlight_image;

  highlight_image=CompareImageChannels(image,reconstruct_image,
    CompositeChannels,metric,distortion,exception);
  return(highlight_image);
}

static size_t GetNumberChannels(const Image *image,const ChannelType channel)
{
  size_t
    channels;

  channels=0;
  if ((channel & RedChannel) != 0)
    channels++;
  if ((channel & GreenChannel) != 0)
    channels++;
  if ((channel & BlueChannel) != 0)
    channels++;
  if (((channel & OpacityChannel) != 0) && (image->matte != MagickFalse))
    channels++;
  if (((channel & IndexChannel) != 0) && (image->colorspace == CMYKColorspace))
    channels++;
  return(channels == 0 ? 1UL : channels);
}

static void SetImageDistortionBounds(const Image *image,
  const Image *reconstruct_image,size_t *columns,size_t *rows)
{ 
  const char
    *artifact;
  
  *columns=MagickMax(image->columns,reconstruct_image->columns);
  *rows=MagickMax(image->rows,reconstruct_image->rows);
  artifact=GetImageArtifact(image,"compare:virtual-pixels");
  if ((artifact != (const char *) NULL) &&
      (IsStringTrue(artifact) == MagickFalse))
    {
      *columns=MagickMin(image->columns,reconstruct_image->columns);
      *rows=MagickMin(image->rows,reconstruct_image->rows);
    }
}   

static inline MagickBooleanType ValidateImageMorphology(
  const Image *magick_restrict image,
  const Image *magick_restrict reconstruct_image)
{
  /*
    Does the image match the reconstructed image morphology?
  */
  if (GetNumberChannels(image,DefaultChannels) !=
      GetNumberChannels(reconstruct_image,DefaultChannels))
    return(MagickFalse);
  return(MagickTrue);
}

MagickExport Image *CompareImageChannels(Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  const MetricType metric,double *distortion,ExceptionInfo *exception)
{
  CacheView
    *highlight_view,
    *image_view,
    *reconstruct_view;

  const char
    *artifact;

  double
    fuzz;

  Image
    *clone_image,
    *difference_image,
    *highlight_image;

  MagickBooleanType
    status;

  MagickPixelPacket
    highlight,
    lowlight,
    zero;

  size_t
    columns,
    rows;

  ssize_t
    y;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(reconstruct_image != (const Image *) NULL);
  assert(reconstruct_image->signature == MagickCoreSignature);
  assert(distortion != (double *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  *distortion=0.0;
  if (metric != PerceptualHashErrorMetric)
    if (ValidateImageMorphology(image,reconstruct_image) == MagickFalse)
      ThrowImageException(ImageError,"ImageMorphologyDiffers");
  status=GetImageChannelDistortion(image,reconstruct_image,channel,metric,
    distortion,exception);
  if (status == MagickFalse)
    return((Image *) NULL);
  clone_image=CloneImage(image,0,0,MagickTrue,exception);
  if (clone_image == (Image *) NULL)
    return((Image *) NULL);
  (void) SetImageMask(clone_image,(Image *) NULL);
  difference_image=CloneImage(clone_image,0,0,MagickTrue,exception);
  clone_image=DestroyImage(clone_image);
  if (difference_image == (Image *) NULL)
    return((Image *) NULL);
  (void) SetImageAlphaChannel(difference_image,OpaqueAlphaChannel);
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  highlight_image=CloneImage(image,columns,rows,MagickTrue,exception);
  if (highlight_image == (Image *) NULL)
    {
      difference_image=DestroyImage(difference_image);
      return((Image *) NULL);
    }
  if (SetImageStorageClass(highlight_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&highlight_image->exception);
      difference_image=DestroyImage(difference_image);
      highlight_image=DestroyImage(highlight_image);
      return((Image *) NULL);
    }
  (void) SetImageMask(highlight_image,(Image *) NULL);
  (void) SetImageAlphaChannel(highlight_image,OpaqueAlphaChannel);
  (void) QueryMagickColor("#f1001ecc",&highlight,exception);
  artifact=GetImageArtifact(image,"compare:highlight-color");
  if (artifact != (const char *) NULL)
    (void) QueryMagickColor(artifact,&highlight,exception);
  (void) QueryMagickColor("#ffffffcc",&lowlight,exception);
  artifact=GetImageArtifact(image,"compare:lowlight-color");
  if (artifact != (const char *) NULL)
    (void) QueryMagickColor(artifact,&lowlight,exception);
  if (highlight_image->colorspace == CMYKColorspace)
    {
      ConvertRGBToCMYK(&highlight);
      ConvertRGBToCMYK(&lowlight);
    }
  /*
    Generate difference image.
  */
  status=MagickTrue;
  fuzz=GetFuzzyColorDistance(image,reconstruct_image);
  GetMagickPixelPacket(image,&zero);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
  highlight_view=AcquireAuthenticCacheView(highlight_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,highlight_image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    MagickBooleanType
      sync;

    MagickPixelPacket
      pixel,
      reconstruct_pixel;

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    IndexPacket
      *magick_restrict highlight_indexes;

    PixelPacket
      *magick_restrict r;

    ssize_t
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    r=QueueCacheViewAuthenticPixels(highlight_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) ||
        (q == (const PixelPacket *) NULL) || (r == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    highlight_indexes=GetCacheViewAuthenticIndexQueue(highlight_view);
    pixel=zero;
    reconstruct_pixel=zero;
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickStatusType
        difference;

      SetMagickPixelPacket(image,p,indexes == (IndexPacket *) NULL ? NULL :
        indexes+x,&pixel);
      SetMagickPixelPacket(reconstruct_image,q,reconstruct_indexes ==
        (IndexPacket *) NULL ? NULL : reconstruct_indexes+x,&reconstruct_pixel);
      difference=MagickFalse;
      if (channel == CompositeChannels)
        {
          if (IsMagickColorSimilar(&pixel,&reconstruct_pixel) == MagickFalse)
            difference=MagickTrue;
        }
      else
        {
          double
            Da,
            distance,
            pixel,
            Sa;

          Sa=QuantumScale*(image->matte != MagickFalse ? (double)
            GetPixelAlpha(p) : ((double) QuantumRange-(double) OpaqueOpacity));
          Da=QuantumScale*(image->matte != MagickFalse ? (double)
            GetPixelAlpha(q) : ((double) QuantumRange-(double) OpaqueOpacity));
          if ((channel & RedChannel) != 0)
            {
              pixel=Sa*(double) GetPixelRed(p)-Da*(double) GetPixelRed(q);
              distance=pixel*pixel;
              if (distance >= fuzz)
                difference=MagickTrue;
            }
          if ((channel & GreenChannel) != 0)
            {
              pixel=Sa*(double) GetPixelGreen(p)-Da*(double) GetPixelGreen(q);
              distance=pixel*pixel;
              if (distance >= fuzz)
                difference=MagickTrue;
            }
          if ((channel & BlueChannel) != 0)
            {
              pixel=Sa*(double) GetPixelBlue(p)-Da*(double) GetPixelBlue(q);
              distance=pixel*pixel;
              if (distance >= fuzz)
                difference=MagickTrue;
            }
          if (((channel & OpacityChannel) != 0) &&
              (image->matte != MagickFalse))
            {
              pixel=(double) GetPixelOpacity(p)-(double) GetPixelOpacity(q);
              distance=pixel*pixel;
              if (distance >= fuzz)
                difference=MagickTrue;
            }
          if (((channel & IndexChannel) != 0) &&
              (image->colorspace == CMYKColorspace))
            {
              pixel=Sa*(double) indexes[x]-Da*(double) reconstruct_indexes[x];
              distance=pixel*pixel;
              if (distance >= fuzz)
                difference=MagickTrue;
            }
        }
      if (difference != MagickFalse)
        SetPixelPacket(highlight_image,&highlight,r,highlight_indexes ==
          (IndexPacket *) NULL ? NULL : highlight_indexes+x);
      else
        SetPixelPacket(highlight_image,&lowlight,r,highlight_indexes ==
          (IndexPacket *) NULL ? NULL : highlight_indexes+x);
      p++;
      q++;
      r++;
    }
    sync=SyncCacheViewAuthenticPixels(highlight_view,exception);
    if (sync == MagickFalse)
      status=MagickFalse;
  }
  highlight_view=DestroyCacheView(highlight_view);
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  (void) CompositeImage(difference_image,image->compose,highlight_image,0,0);
  highlight_image=DestroyImage(highlight_image);
  if (status == MagickFalse)
    difference_image=DestroyImage(difference_image);
  return(difference_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e C h a n n e l D i s t o r t i o n                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageChannelDistortion() compares one or more image channels of an image
%  to a reconstructed image and returns the specified distortion metric.
%
%  The format of the GetImageChannelDistortion method is:
%
%      MagickBooleanType GetImageChannelDistortion(const Image *image,
%        const Image *reconstruct_image,const ChannelType channel,
%        const MetricType metric,double *distortion,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o reconstruct_image: the reconstruct image.
%
%    o channel: the channel.
%
%    o metric: the metric.
%
%    o distortion: the computed distortion between the images.
%
%    o exception: return any errors or warnings in this structure.
%
*/

MagickExport MagickBooleanType GetImageDistortion(Image *image,
  const Image *reconstruct_image,const MetricType metric,double *distortion,
  ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  status=GetImageChannelDistortion(image,reconstruct_image,CompositeChannels,
    metric,distortion,exception);
  return(status);
}

static MagickBooleanType GetAbsoluteDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,double *distortion,
  ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reconstruct_view;

  MagickBooleanType
    status;

  size_t
    columns,
    rows;

  ssize_t
    i,
    y;

  /*
    Compute the absolute difference in pixels between two images.
  */
  status=MagickTrue;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      channel_distortion[CompositeChannels+1];

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      i,
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    (void) memset(channel_distortion,0,sizeof(channel_distortion));
    for (x=0; x < (ssize_t) columns; x++)
    {
      double
        Da,
        delta,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      Da=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(q) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      if ((channel & RedChannel) != 0)
        {
          delta=QuantumScale*(Sa*(double) GetPixelRed(p)-Da*(double)
            GetPixelRed(q));
          channel_distortion[RedChannel]+=fabs(delta);
          channel_distortion[CompositeChannels]+=fabs(delta);
        }
      if ((channel & GreenChannel) != 0)
        {
          delta=QuantumScale*(Sa*(double) GetPixelGreen(p)-Da*(double)
            GetPixelGreen(q));
          channel_distortion[RedChannel]+=fabs(delta);
          channel_distortion[CompositeChannels]+=fabs(delta);
        }
      if ((channel & BlueChannel) != 0)
        {
          delta=QuantumScale*(Sa*(double) GetPixelBlue(p)-Da*(double)
            GetPixelBlue(q));
          channel_distortion[RedChannel]+=fabs(delta);
          channel_distortion[CompositeChannels]+=fabs(delta);
        }
      if (((channel & OpacityChannel) != 0) &&
          (image->matte != MagickFalse))
        {
          delta=QuantumScale*((double) GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          channel_distortion[RedChannel]+=fabs(delta);
          channel_distortion[CompositeChannels]+=fabs(delta);
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace))
        {
          delta=QuantumScale*(Sa*(double) indexes[x]-Da*(double)
            reconstruct_indexes[x]);
          channel_distortion[RedChannel]+=fabs(delta);
          channel_distortion[CompositeChannels]+=fabs(delta);
        }
      p++;
      q++;
    }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
    #pragma omp critical (MagickCore_GetAbsoluteDistortion)
#endif
    for (i=0; i <= (ssize_t) CompositeChannels; i++)
      distortion[i]+=channel_distortion[i];
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  distortion[CompositeChannels]/=(double) GetNumberChannels(image,channel);
  for (i=0; i <= (ssize_t) CompositeChannels; i++)
    distortion[i]/=((double) columns*rows);
  return(status);
}

static MagickBooleanType GetFuzzDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  double *distortion,ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reconstruct_view;

  MagickBooleanType
    status;

  ssize_t
    i;

  size_t
    columns,
    rows;

  ssize_t
    y;

  status=MagickTrue;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      channel_distortion[CompositeChannels+1];

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      i,
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    (void) memset(channel_distortion,0,sizeof(channel_distortion));
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        distance,
        Da,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      Da=QuantumScale*(reconstruct_image->matte != MagickFalse ?
        (double) GetPixelAlpha(q) : ((double) QuantumRange-(double)
        OpaqueOpacity));
      if ((channel & RedChannel) != 0)
        {
          distance=QuantumScale*(Sa*(double) GetPixelRed(p)-Da*(double)
            GetPixelRed(q));
          channel_distortion[RedChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if ((channel & GreenChannel) != 0)
        {
          distance=QuantumScale*(Sa*(double) GetPixelGreen(p)-Da*(double)
            GetPixelGreen(q));
          channel_distortion[GreenChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if ((channel & BlueChannel) != 0)
        {
          distance=QuantumScale*(Sa*(double) GetPixelBlue(p)-Da*(double)
            GetPixelBlue(q));
          channel_distortion[BlueChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if (((channel & OpacityChannel) != 0) && ((image->matte != MagickFalse) ||
          (reconstruct_image->matte != MagickFalse)))
        {
          distance=QuantumScale*((image->matte != MagickFalse ? (double)
            GetPixelOpacity(p) : (double) OpaqueOpacity)-
            (reconstruct_image->matte != MagickFalse ?
            (double) GetPixelOpacity(q): (double) OpaqueOpacity));
          channel_distortion[OpacityChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace) &&
          (reconstruct_image->colorspace == CMYKColorspace))
        {
          distance=QuantumScale*(Sa*(double) GetPixelIndex(indexes+x)-
            Da*(double) GetPixelIndex(reconstruct_indexes+x));
          channel_distortion[BlackChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      p++;
      q++;
    }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
    #pragma omp critical (MagickCore_GetFuzzDistortion)
#endif
    for (i=0; i <= (ssize_t) CompositeChannels; i++)
      distortion[i]+=channel_distortion[i];
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  distortion[CompositeChannels]/=(double) GetNumberChannels(image,channel);
  for (i=0; i <= (ssize_t) CompositeChannels; i++)
    distortion[i]/=((double) columns*rows);
  distortion[CompositeChannels]=sqrt(distortion[CompositeChannels]);
  return(status);
}

static MagickBooleanType GetMeanAbsoluteDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  double *distortion,ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reconstruct_view;

  MagickBooleanType
    status;

  size_t
    columns,
    rows;

  ssize_t
    i,
    y;

  status=MagickTrue;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      channel_distortion[CompositeChannels+1];

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      i,
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    (void) memset(channel_distortion,0,sizeof(channel_distortion));
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        distance,
        Da,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      Da=QuantumScale*(reconstruct_image->matte != MagickFalse ?
        (double) GetPixelAlpha(q) : ((double) QuantumRange-(double)
        OpaqueOpacity));
      if ((channel & RedChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelRed(p)-Da*
            (double) GetPixelRed(q));
          channel_distortion[RedChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
        }
      if ((channel & GreenChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelGreen(p)-Da*
            (double) GetPixelGreen(q));
          channel_distortion[GreenChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
        }
      if ((channel & BlueChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelBlue(p)-Da*
            (double) GetPixelBlue(q));
          channel_distortion[BlueChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
        }
      if (((channel & OpacityChannel) != 0) &&
          (image->matte != MagickFalse))
        {
          distance=QuantumScale*fabs((double) GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          channel_distortion[OpacityChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace))
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelIndex(indexes+x)-Da*
            (double) GetPixelIndex(reconstruct_indexes+x));
          channel_distortion[BlackChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
        }
      p++;
      q++;
    }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
    #pragma omp critical (MagickCore_GetMeanAbsoluteError)
#endif
    for (i=0; i <= (ssize_t) CompositeChannels; i++)
      distortion[i]+=channel_distortion[i];
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  for (i=0; i <= (ssize_t) CompositeChannels; i++)
    distortion[i]/=((double) columns*rows);
  distortion[CompositeChannels]/=(double) GetNumberChannels(image,channel);
  return(status);
}

static MagickBooleanType GetMeanErrorPerPixel(Image *image,
  const Image *reconstruct_image,const ChannelType channel,double *distortion,
  ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reconstruct_view;

  double
    maximum_error = MagickMinimumValue;

  MagickBooleanType
    status;

  size_t
    columns,
    rows;

  ssize_t
    i,
    y;

  status=MagickTrue;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      channel_distortion[CompositeChannels+1],
      local_maximum = MinimumValue;

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      i,
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    (void) memset(channel_distortion,0,sizeof(channel_distortion));
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        distance,
        Da,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      Da=QuantumScale*(reconstruct_image->matte != MagickFalse ?
        (double) GetPixelAlpha(q) : ((double) QuantumRange-(double)
        OpaqueOpacity));
      if ((channel & RedChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelRed(p)-Da*
            (double) GetPixelRed(q));
          channel_distortion[RedChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
          if (distance > local_maximum)
            local_maximum=distance;
        }
      if ((channel & GreenChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelGreen(p)-Da*
            (double) GetPixelGreen(q));
          channel_distortion[GreenChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
          if (distance > local_maximum)
            local_maximum=distance;
        }
      if ((channel & BlueChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelBlue(p)-Da*
            (double) GetPixelBlue(q));
          channel_distortion[BlueChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
          if (distance > local_maximum)
            local_maximum=distance;
        }
      if (((channel & OpacityChannel) != 0) &&
          (image->matte != MagickFalse))
        {
          distance=QuantumScale*fabs((double) GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          channel_distortion[OpacityChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
          if (distance > local_maximum)
            local_maximum=distance;
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace))
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelIndex(indexes+x)-Da*
            (double) GetPixelIndex(reconstruct_indexes+x));
          channel_distortion[BlackChannel]+=distance;
          channel_distortion[CompositeChannels]+=distance;
          if (distance > local_maximum)
            local_maximum=distance;
        }
      p++;
      q++;
    }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
    #pragma omp critical (MagickCore_GetMeanAbsoluteError)
#endif
    {
      for (i=0; i <= (ssize_t) CompositeChannels; i++)
        distortion[i]+=channel_distortion[i];
      if (local_maximum > maximum_error)
        maximum_error=local_maximum;
    }
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  distortion[CompositeChannels]/=(double) GetNumberChannels(image,channel);
  for (i=0; i <= (ssize_t) CompositeChannels; i++)
    distortion[i]/=((double) columns*rows);
  image->error.mean_error_per_pixel=distortion[CompositeChannels];
  image->error.normalized_mean_error=distortion[CompositeChannels];
  image->error.normalized_maximum_error=QuantumScale*maximum_error;
  return(status);
}

static MagickBooleanType GetMeanSquaredDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  double *distortion,ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reconstruct_view;

  double
    area;

  MagickBooleanType
    status;

  size_t
    columns,
    rows;

  ssize_t
    i,
    y;

  status=MagickTrue;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      channel_distortion[CompositeChannels+1];

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      i,
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    (void) memset(channel_distortion,0,sizeof(channel_distortion));
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        distance,
        Da,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      Da=QuantumScale*(reconstruct_image->matte != MagickFalse ?
        (double) GetPixelAlpha(q) : ((double) QuantumRange-(double)
        OpaqueOpacity));
      if ((channel & RedChannel) != 0)
        {
          distance=QuantumScale*(Sa*(double) GetPixelRed(p)-Da*(double)
            GetPixelRed(q));
          channel_distortion[RedChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if ((channel & GreenChannel) != 0)
        {
          distance=QuantumScale*(Sa*(double) GetPixelGreen(p)-Da*(double)
            GetPixelGreen(q));
          channel_distortion[GreenChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if ((channel & BlueChannel) != 0)
        {
          distance=QuantumScale*(Sa*(double) GetPixelBlue(p)-Da*(double)
            GetPixelBlue(q));
          channel_distortion[BlueChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if (((channel & OpacityChannel) != 0) &&
          (image->matte != MagickFalse))
        {
          distance=QuantumScale*((double) GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          channel_distortion[OpacityChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace) &&
          (reconstruct_image->colorspace == CMYKColorspace))
        {
          distance=QuantumScale*(Sa*(double) GetPixelIndex(indexes+x)-Da*
            (double) GetPixelIndex(reconstruct_indexes+x));
          channel_distortion[BlackChannel]+=distance*distance;
          channel_distortion[CompositeChannels]+=distance*distance;
        }
      p++;
      q++;
    }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
    #pragma omp critical (MagickCore_GetMeanSquaredError)
#endif
    for (i=0; i <= (ssize_t) CompositeChannels; i++)
      distortion[i]+=channel_distortion[i];
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  area=PerceptibleReciprocal((double) columns*rows);
  distortion[CompositeChannels]/=(double) GetNumberChannels(image,channel);
  for (i=0; i <= (ssize_t) CompositeChannels; i++)
    distortion[i]*=area;
  return(status);
}

static MagickBooleanType GetNormalizedCrossCorrelationDistortion(
  const Image *image,const Image *reconstruct_image,const ChannelType channel,
  double *distortion,ExceptionInfo *exception)
{
#define SimilarityImageTag  "Similarity/Image"

  CacheView
    *image_view,
    *reconstruct_view;

  ChannelStatistics
    *image_statistics,
    *reconstruct_statistics;

  double
    alpha_variance[CompositeChannels+1],
    beta_variance[CompositeChannels+1];

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  ssize_t
    i;

  size_t
    columns,
    rows;

  ssize_t
    y;

  /*
    Normalize to account for variation due to lighting and exposure condition.
  */
  image_statistics=GetImageChannelStatistics(image,exception);
  reconstruct_statistics=GetImageChannelStatistics(reconstruct_image,exception);
  if ((image_statistics == (ChannelStatistics *) NULL) ||
      (reconstruct_statistics == (ChannelStatistics *) NULL))
    {
      if (image_statistics != (ChannelStatistics *) NULL)
        image_statistics=(ChannelStatistics *) RelinquishMagickMemory(
          image_statistics);
      if (reconstruct_statistics != (ChannelStatistics *) NULL)
        reconstruct_statistics=(ChannelStatistics *) RelinquishMagickMemory(
          reconstruct_statistics);
      return(MagickFalse);
    }
  (void) memset(distortion,0,(CompositeChannels+1)*sizeof(*distortion));
  (void) memset(alpha_variance,0,(CompositeChannels+1)*sizeof(*alpha_variance));
  (void) memset(beta_variance,0,(CompositeChannels+1)*sizeof(*beta_variance));
  status=MagickTrue;
  progress=0;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    reduction(+:distortion[:CompositeChannels+1]) \
    reduction(+:alpha_variance[:CompositeChannels+1]) \
    reduction(+:beta_variance[:CompositeChannels+1]) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        alpha,
        beta,
        Da,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        (double) QuantumRange);
      Da=QuantumScale*(reconstruct_image->matte != MagickFalse ?
        (double) GetPixelAlpha(q) : (double) QuantumRange);
      if ((channel & RedChannel) != 0)
        {
          alpha=QuantumScale*fabs(Sa*(double) GetPixelRed(p)-
            image_statistics[RedChannel].mean);
          beta=QuantumScale*fabs(Da*(double) GetPixelRed(q)-
            reconstruct_statistics[RedChannel].mean);
          distortion[RedChannel]+=alpha*beta;
          alpha_variance[RedChannel]+=alpha*alpha;
          beta_variance[RedChannel]+=beta*beta;
        }
      if ((channel & GreenChannel) != 0)
        {
          alpha=QuantumScale*fabs(Sa*(double) GetPixelGreen(p)-
            image_statistics[GreenChannel].mean);
          beta=QuantumScale*fabs(Da*(double) GetPixelGreen(q)-
            reconstruct_statistics[GreenChannel].mean);
          distortion[GreenChannel]+=alpha*beta;
          alpha_variance[GreenChannel]+=alpha*alpha;
          beta_variance[GreenChannel]+=beta*beta;
        }
      if ((channel & BlueChannel) != 0)
        {
          alpha=QuantumScale*fabs(Sa*(double) GetPixelBlue(p)-
            image_statistics[BlueChannel].mean);
          beta=QuantumScale*fabs(Da*(double) GetPixelBlue(q)-
            reconstruct_statistics[BlueChannel].mean);
          distortion[BlueChannel]+=alpha*beta;
          alpha_variance[BlueChannel]+=alpha*alpha;
          beta_variance[BlueChannel]+=beta*beta;
        }
      if (((channel & OpacityChannel) != 0) && (image->matte != MagickFalse))
        {
          alpha=QuantumScale*fabs((double) GetPixelAlpha(p)-
            image_statistics[AlphaChannel].mean);
          beta=QuantumScale*fabs((double) GetPixelAlpha(q)-
            reconstruct_statistics[AlphaChannel].mean);
          distortion[OpacityChannel]+=alpha*beta;
          alpha_variance[OpacityChannel]+=alpha*alpha;
          beta_variance[OpacityChannel]+=beta*beta;
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace) &&
          (reconstruct_image->colorspace == CMYKColorspace))
        {
          alpha=QuantumScale*fabs(Sa*(double) GetPixelIndex(indexes+x)-
            image_statistics[BlackChannel].mean);
          beta=QuantumScale*fabs(Da*(double) GetPixelIndex(reconstruct_indexes+
            x)-reconstruct_statistics[BlackChannel].mean);
          distortion[BlackChannel]+=alpha*beta;
          alpha_variance[BlackChannel]+=alpha*alpha;
          beta_variance[BlackChannel]+=beta*beta;
        }
      p++;
      q++;
    }
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,SimilarityImageTag,progress,rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  /*
    Divide by the standard deviation.
  */
  for (i=0; i < (ssize_t) CompositeChannels; i++)
  {
    distortion[i]/=sqrt(alpha_variance[i]*beta_variance[i]);
    if (fabs(distortion[i]) >= MagickEpsilon)
      distortion[CompositeChannels]+=distortion[i];
  }
  distortion[CompositeChannels]=distortion[CompositeChannels]/
    GetNumberChannels(image,channel);
  /*
    Free resources.
  */
  reconstruct_statistics=(ChannelStatistics *) RelinquishMagickMemory(
    reconstruct_statistics);
  image_statistics=(ChannelStatistics *) RelinquishMagickMemory(
    image_statistics);
  return(status);
}

static MagickBooleanType GetPeakAbsoluteDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  double *distortion,ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reconstruct_view;

  MagickBooleanType
    status;

  size_t
    columns,
    rows;

  ssize_t
    y;

  status=MagickTrue;
  (void) memset(distortion,0,(CompositeChannels+1)*sizeof(*distortion));
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,rows,1)
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      channel_distortion[CompositeChannels+1];

    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      i,
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    (void) memset(channel_distortion,0,(CompositeChannels+1)*
      sizeof(*channel_distortion));
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        distance,
        Da,
        Sa;

      Sa=QuantumScale*(image->matte != MagickFalse ? (double) GetPixelAlpha(p) :
        ((double) QuantumRange-(double) OpaqueOpacity));
      Da=QuantumScale*(reconstruct_image->matte != MagickFalse ?
        (double) GetPixelAlpha(q) : ((double) QuantumRange-(double)
        OpaqueOpacity));
      if ((channel & RedChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelRed(p)-Da*
            (double) GetPixelRed(q));
          if (distance > channel_distortion[RedChannel])
            channel_distortion[RedChannel]=distance;
          if (distance > channel_distortion[CompositeChannels])
            channel_distortion[CompositeChannels]=distance;
        }
      if ((channel & GreenChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelGreen(p)-Da*
            (double) GetPixelGreen(q));
          if (distance > channel_distortion[GreenChannel])
            channel_distortion[GreenChannel]=distance;
          if (distance > channel_distortion[CompositeChannels])
            channel_distortion[CompositeChannels]=distance;
        }
      if ((channel & BlueChannel) != 0)
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelBlue(p)-Da*
            (double) GetPixelBlue(q));
          if (distance > channel_distortion[BlueChannel])
            channel_distortion[BlueChannel]=distance;
          if (distance > channel_distortion[CompositeChannels])
            channel_distortion[CompositeChannels]=distance;
        }
      if (((channel & OpacityChannel) != 0) &&
          (image->matte != MagickFalse))
        {
          distance=QuantumScale*fabs((double) GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          if (distance > channel_distortion[OpacityChannel])
            channel_distortion[OpacityChannel]=distance;
          if (distance > channel_distortion[CompositeChannels])
            channel_distortion[CompositeChannels]=distance;
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace) &&
          (reconstruct_image->colorspace == CMYKColorspace))
        {
          distance=QuantumScale*fabs(Sa*(double) GetPixelIndex(indexes+x)-Da*
            (double) GetPixelIndex(reconstruct_indexes+x));
          if (distance > channel_distortion[BlackChannel])
            channel_distortion[BlackChannel]=distance;
          if (distance > channel_distortion[CompositeChannels])
            channel_distortion[CompositeChannels]=distance;
        }
      p++;
      q++;
    }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
    #pragma omp critical (MagickCore_GetPeakAbsoluteError)
#endif
    for (i=0; i <= (ssize_t) CompositeChannels; i++)
      if (channel_distortion[i] > distortion[i])
        distortion[i]=channel_distortion[i];
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  return(status);
}

static MagickBooleanType GetPeakSignalToNoiseRatio(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  double *distortion,ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  status=GetMeanSquaredDistortion(image,reconstruct_image,channel,distortion,
    exception);
  if ((channel & RedChannel) != 0)
    {
      if (distortion[RedChannel] < MagickEpsilon)
        distortion[RedChannel]=1.0;
      else
        if (distortion[RedChannel] >= 1.0)
          distortion[RedChannel]=0.0;
        else
          distortion[RedChannel]=10.0*log10(PerceptibleReciprocal(
            distortion[RedChannel]))/MagickPSNRDistortion;
    }
  if ((channel & GreenChannel) != 0)
    {
      if (distortion[GreenChannel] < MagickEpsilon)
        distortion[GreenChannel]=1.0;
      else
        if (distortion[GreenChannel] >= 1.0)
          distortion[GreenChannel]=0.0;
        else
          distortion[GreenChannel]=10.0*log10(PerceptibleReciprocal(
            distortion[GreenChannel]))/MagickPSNRDistortion;
    }
  if ((channel & BlueChannel) != 0)
    {
      if (distortion[BlueChannel] < MagickEpsilon)
        distortion[BlueChannel]=1.0;
      else 
        if (distortion[BlueChannel] >= 1.0)
          distortion[BlueChannel]=0.0;
        else
          distortion[BlueChannel]=10.0*log10(PerceptibleReciprocal(
            distortion[BlueChannel]))/MagickPSNRDistortion;
    }
  if (((channel & OpacityChannel) != 0) && (image->matte != MagickFalse))
    {
      if (distortion[OpacityChannel] < MagickEpsilon)
        distortion[OpacityChannel]=1.0;
      else
        if (distortion[OpacityChannel] >= 1.0)
          distortion[OpacityChannel]=0.0;
        else
          distortion[OpacityChannel]=10.0*log10(PerceptibleReciprocal(
            distortion[OpacityChannel]))/MagickPSNRDistortion;
    }
  if (((channel & IndexChannel) != 0) && (image->colorspace == CMYKColorspace))
    {
      if (distortion[BlackChannel] < MagickEpsilon)
        distortion[BlackChannel]=1.0;
      else
        if (distortion[BlackChannel] >= 1.0)
          distortion[BlackChannel]=0.0;
        else
          distortion[BlackChannel]=10.0*log10(PerceptibleReciprocal(
            distortion[BlackChannel]))/MagickPSNRDistortion;
    }
  if (distortion[CompositeChannels] < MagickEpsilon)
    distortion[CompositeChannels]=1.0;
  else
    if (distortion[CompositeChannels] >= 1.0)
      distortion[CompositeChannels]=0.0;
    else
      distortion[CompositeChannels]=10.0*log10(PerceptibleReciprocal(
        distortion[CompositeChannels]))/MagickPSNRDistortion;
  return(status);
}

static MagickBooleanType GetPerceptualHashDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,double *distortion,
  ExceptionInfo *exception)
{
  ChannelPerceptualHash
    *image_phash,
    *reconstruct_phash;

  double
    difference;

  ssize_t
    i;

  /*
    Compute perceptual hash in the sRGB colorspace.
  */
  image_phash=GetImageChannelPerceptualHash(image,exception);
  if (image_phash == (ChannelPerceptualHash *) NULL)
    return(MagickFalse);
  reconstruct_phash=GetImageChannelPerceptualHash(reconstruct_image,exception);
  if (reconstruct_phash == (ChannelPerceptualHash *) NULL)
    {
      image_phash=(ChannelPerceptualHash *) RelinquishMagickMemory(image_phash);
      return(MagickFalse);
    }
  for (i=0; i < MaximumNumberOfImageMoments; i++)
  {
    /*
      Compute sum of moment differences squared.
    */
    if ((channel & RedChannel) != 0)
      {
        difference=reconstruct_phash[RedChannel].P[i]-
          image_phash[RedChannel].P[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[RedChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if ((channel & GreenChannel) != 0)
      {
        difference=reconstruct_phash[GreenChannel].P[i]-
          image_phash[GreenChannel].P[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[GreenChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if ((channel & BlueChannel) != 0)
      {
        difference=reconstruct_phash[BlueChannel].P[i]-
          image_phash[BlueChannel].P[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[BlueChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if (((channel & OpacityChannel) != 0) && (image->matte != MagickFalse) &&
        (reconstruct_image->matte != MagickFalse))
      {
        difference=reconstruct_phash[OpacityChannel].P[i]-
          image_phash[OpacityChannel].P[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[OpacityChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if (((channel & IndexChannel) != 0) &&
        (image->colorspace == CMYKColorspace) &&
        (reconstruct_image->colorspace == CMYKColorspace))
      {
        difference=reconstruct_phash[IndexChannel].P[i]-
          image_phash[IndexChannel].P[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[IndexChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
  }
  /*
    Compute perceptual hash in the HCLP colorspace.
  */
  for (i=0; i < MaximumNumberOfImageMoments; i++)
  {
    /*
      Compute sum of moment differences squared.
    */
    if ((channel & RedChannel) != 0)
      {
        difference=reconstruct_phash[RedChannel].Q[i]-
          image_phash[RedChannel].Q[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[RedChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if ((channel & GreenChannel) != 0)
      {
        difference=reconstruct_phash[GreenChannel].Q[i]-
          image_phash[GreenChannel].Q[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[GreenChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if ((channel & BlueChannel) != 0)
      {
        difference=reconstruct_phash[BlueChannel].Q[i]-
          image_phash[BlueChannel].Q[i];
        distortion[BlueChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if (((channel & OpacityChannel) != 0) && (image->matte != MagickFalse) &&
        (reconstruct_image->matte != MagickFalse))
      {
        difference=reconstruct_phash[OpacityChannel].Q[i]-
          image_phash[OpacityChannel].Q[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[OpacityChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
    if (((channel & IndexChannel) != 0) &&
        (image->colorspace == CMYKColorspace) &&
        (reconstruct_image->colorspace == CMYKColorspace))
      {
        difference=reconstruct_phash[IndexChannel].Q[i]-
          image_phash[IndexChannel].Q[i];
        if (IsNaN(difference) != 0)
          difference=0.0;
        distortion[IndexChannel]+=difference*difference;
        distortion[CompositeChannels]+=difference*difference;
      }
  }
  /*
    Free resources.
  */
  reconstruct_phash=(ChannelPerceptualHash *) RelinquishMagickMemory(
    reconstruct_phash);
  image_phash=(ChannelPerceptualHash *) RelinquishMagickMemory(image_phash);
  return(MagickTrue);
}

static MagickBooleanType GetRootMeanSquaredDistortion(const Image *image,
  const Image *reconstruct_image,const ChannelType channel,double *distortion,
  ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  status=GetMeanSquaredDistortion(image,reconstruct_image,channel,distortion,
    exception);
  if ((channel & RedChannel) != 0)
    distortion[RedChannel]=sqrt(distortion[RedChannel]);
  if ((channel & GreenChannel) != 0)
    distortion[GreenChannel]=sqrt(distortion[GreenChannel]);
  if ((channel & BlueChannel) != 0)
    distortion[BlueChannel]=sqrt(distortion[BlueChannel]);
  if (((channel & OpacityChannel) != 0) &&
      (image->matte != MagickFalse))
    distortion[OpacityChannel]=sqrt(distortion[OpacityChannel]);
  if (((channel & IndexChannel) != 0) &&
      (image->colorspace == CMYKColorspace))
    distortion[BlackChannel]=sqrt(distortion[BlackChannel]);
  distortion[CompositeChannels]=sqrt(distortion[CompositeChannels]);
  return(status);
}

MagickExport MagickBooleanType GetImageChannelDistortion(Image *image,
  const Image *reconstruct_image,const ChannelType channel,
  const MetricType metric,double *distortion,ExceptionInfo *exception)
{
  double
    *channel_distortion;

  MagickBooleanType
    status;

  size_t
    length;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(reconstruct_image != (const Image *) NULL);
  assert(reconstruct_image->signature == MagickCoreSignature);
  assert(distortion != (double *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  *distortion=0.0;
  if (metric != PerceptualHashErrorMetric)
    if (ValidateImageMorphology(image,reconstruct_image) == MagickFalse)
      ThrowBinaryException(ImageError,"ImageMorphologyDiffers",image->filename);
  /*
    Get image distortion.
  */
  length=CompositeChannels+1UL;
  channel_distortion=(double *) AcquireQuantumMemory(length,
    sizeof(*channel_distortion));
  if (channel_distortion == (double *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  (void) memset(channel_distortion,0,length*sizeof(*channel_distortion));
  switch (metric)
  {
    case AbsoluteErrorMetric:
    {
      status=GetAbsoluteDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case FuzzErrorMetric:
    {
      status=GetFuzzDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case MeanAbsoluteErrorMetric:
    {
      status=GetMeanAbsoluteDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case MeanErrorPerPixelMetric:
    {
      status=GetMeanErrorPerPixel(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case MeanSquaredErrorMetric:
    {
      status=GetMeanSquaredDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case NormalizedCrossCorrelationErrorMetric:
    default:
    {
      status=GetNormalizedCrossCorrelationDistortion(image,reconstruct_image,
        channel,channel_distortion,exception);
      break;
    }
    case PeakAbsoluteErrorMetric:
    {
      status=GetPeakAbsoluteDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case PeakSignalToNoiseRatioMetric:
    {
      status=GetPeakSignalToNoiseRatio(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case PerceptualHashErrorMetric:
    {
      status=GetPerceptualHashDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
    case RootMeanSquaredErrorMetric:
    {
      status=GetRootMeanSquaredDistortion(image,reconstruct_image,channel,
        channel_distortion,exception);
      break;
    }
  }
  *distortion=channel_distortion[CompositeChannels];
  channel_distortion=(double *) RelinquishMagickMemory(channel_distortion);
  (void) FormatImageProperty(image,"distortion","%.*g",GetMagickPrecision(),
    *distortion);
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e C h a n n e l D i s t o r t i o n s                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageChannelDistortions() compares the image channels of an image to a
%  reconstructed image and returns the specified distortion metric for each
%  channel.
%
%  The format of the GetImageChannelDistortions method is:
%
%      double *GetImageChannelDistortions(const Image *image,
%        const Image *reconstruct_image,const MetricType metric,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o reconstruct_image: the reconstruct image.
%
%    o metric: the metric.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport double *GetImageChannelDistortions(Image *image,
  const Image *reconstruct_image,const MetricType metric,
  ExceptionInfo *exception)
{
  double
    *channel_distortion;

  MagickBooleanType
    status;

  size_t
    length;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(reconstruct_image != (const Image *) NULL);
  assert(reconstruct_image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (metric != PerceptualHashErrorMetric)
    if (ValidateImageMorphology(image,reconstruct_image) == MagickFalse)
      {
        (void) ThrowMagickException(&image->exception,GetMagickModule(),
          ImageError,"ImageMorphologyDiffers","`%s'",image->filename);
        return((double *) NULL);
      }
  /*
    Get image distortion.
  */
  length=CompositeChannels+1UL;
  channel_distortion=(double *) AcquireQuantumMemory(length,
    sizeof(*channel_distortion));
  if (channel_distortion == (double *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  (void) memset(channel_distortion,0,length*
    sizeof(*channel_distortion));
  status=MagickTrue;
  switch (metric)
  {
    case AbsoluteErrorMetric:
    {
      status=GetAbsoluteDistortion(image,reconstruct_image,CompositeChannels,
        channel_distortion,exception);
      break;
    }
    case FuzzErrorMetric:
    {
      status=GetFuzzDistortion(image,reconstruct_image,CompositeChannels,
        channel_distortion,exception);
      break;
    }
    case MeanAbsoluteErrorMetric:
    {
      status=GetMeanAbsoluteDistortion(image,reconstruct_image,
        CompositeChannels,channel_distortion,exception);
      break;
    }
    case MeanErrorPerPixelMetric:
    {
      status=GetMeanErrorPerPixel(image,reconstruct_image,CompositeChannels,
        channel_distortion,exception);
      break;
    }
    case MeanSquaredErrorMetric:
    {
      status=GetMeanSquaredDistortion(image,reconstruct_image,CompositeChannels,
        channel_distortion,exception);
      break;
    }
    case NormalizedCrossCorrelationErrorMetric:
    default:
    {
      status=GetNormalizedCrossCorrelationDistortion(image,reconstruct_image,
        CompositeChannels,channel_distortion,exception);
      break;
    }
    case PeakAbsoluteErrorMetric:
    {
      status=GetPeakAbsoluteDistortion(image,reconstruct_image,
        CompositeChannels,channel_distortion,exception);
      break;
    }
    case PeakSignalToNoiseRatioMetric:
    {
      status=GetPeakSignalToNoiseRatio(image,reconstruct_image,
        CompositeChannels,channel_distortion,exception);
      break;
    }
    case PerceptualHashErrorMetric:
    {
      status=GetPerceptualHashDistortion(image,reconstruct_image,
        CompositeChannels,channel_distortion,exception);
      break;
    }
    case RootMeanSquaredErrorMetric:
    {
      status=GetRootMeanSquaredDistortion(image,reconstruct_image,
        CompositeChannels,channel_distortion,exception);
      break;
    }
  }
  if (status == MagickFalse)
    {
      channel_distortion=(double *) RelinquishMagickMemory(channel_distortion);
      return((double *) NULL);
    }
  return(channel_distortion);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  I s I m a g e s E q u a l                                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  IsImagesEqual() measures the difference between colors at each pixel
%  location of two images.  A value other than 0 means the colors match
%  exactly.  Otherwise an error measure is computed by summing over all
%  pixels in an image the distance squared in RGB space between each image
%  pixel and its corresponding pixel in the reconstruct image.  The error
%  measure is assigned to these image members:
%
%    o mean_error_per_pixel:  The mean error for any single pixel in
%      the image.
%
%    o normalized_mean_error:  The normalized mean quantization error for
%      any single pixel in the image.  This distance measure is normalized to
%      a range between 0 and 1.  It is independent of the range of red, green,
%      and blue values in the image.
%
%    o normalized_maximum_error:  The normalized maximum quantization
%      error for any single pixel in the image.  This distance measure is
%      normalized to a range between 0 and 1.  It is independent of the range
%      of red, green, and blue values in your image.
%
%  A small normalized mean square error, accessed as
%  image->normalized_mean_error, suggests the images are very similar in
%  spatial layout and color.
%
%  The format of the IsImagesEqual method is:
%
%      MagickBooleanType IsImagesEqual(Image *image,
%        const Image *reconstruct_image)
%
%  A description of each parameter follows.
%
%    o image: the image.
%
%    o reconstruct_image: the reconstruct image.
%
*/
MagickExport MagickBooleanType IsImagesEqual(Image *image,
  const Image *reconstruct_image)
{
  CacheView
    *image_view,
    *reconstruct_view;

  ExceptionInfo
    *exception;

  MagickBooleanType
    status;

  MagickRealType
    area,
    gamma,
    maximum_error,
    mean_error,
    mean_error_per_pixel;

  size_t
    columns,
    rows;

  ssize_t
    y;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(reconstruct_image != (const Image *) NULL);
  assert(reconstruct_image->signature == MagickCoreSignature);
  exception=(&image->exception);
  if (ValidateImageMorphology(image,reconstruct_image) == MagickFalse)
    ThrowBinaryException(ImageError,"ImageMorphologyDiffers",image->filename);
  area=0.0;
  maximum_error=0.0;
  mean_error_per_pixel=0.0;
  mean_error=0.0;
  SetImageDistortionBounds(image,reconstruct_image,&columns,&rows);
  image_view=AcquireVirtualCacheView(image,exception);
  reconstruct_view=AcquireVirtualCacheView(reconstruct_image,exception);
  for (y=0; y < (ssize_t) rows; y++)
  {
    const IndexPacket
      *magick_restrict indexes,
      *magick_restrict reconstruct_indexes;

    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      x;

    p=GetCacheViewVirtualPixels(image_view,0,y,columns,1,exception);
    q=GetCacheViewVirtualPixels(reconstruct_view,0,y,columns,1,exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      break;
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reconstruct_indexes=GetCacheViewVirtualIndexQueue(reconstruct_view);
    for (x=0; x < (ssize_t) columns; x++)
    {
      MagickRealType
        distance;

      distance=fabs((double) GetPixelRed(p)-(double) GetPixelRed(q));
      mean_error_per_pixel+=distance;
      mean_error+=distance*distance;
      if (distance > maximum_error)
        maximum_error=distance;
      area++;
      distance=fabs((double) GetPixelGreen(p)-(double) GetPixelGreen(q));
      mean_error_per_pixel+=distance;
      mean_error+=distance*distance;
      if (distance > maximum_error)
        maximum_error=distance;
      area++;
      distance=fabs((double) GetPixelBlue(p)-(double) GetPixelBlue(q));
      mean_error_per_pixel+=distance;
      mean_error+=distance*distance;
      if (distance > maximum_error)
        maximum_error=distance;
      area++;
      if (image->matte != MagickFalse)
        {
          distance=fabs((double) GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          mean_error_per_pixel+=distance;
          mean_error+=distance*distance;
          if (distance > maximum_error)
            maximum_error=distance;
          area++;
        }
      if ((image->colorspace == CMYKColorspace) &&
          (reconstruct_image->colorspace == CMYKColorspace))
        {
          distance=fabs((double) GetPixelIndex(indexes+x)-(double)
            GetPixelIndex(reconstruct_indexes+x));
          mean_error_per_pixel+=distance;
          mean_error+=distance*distance;
          if (distance > maximum_error)
            maximum_error=distance;
          area++;
        }
      p++;
      q++;
    }
  }
  reconstruct_view=DestroyCacheView(reconstruct_view);
  image_view=DestroyCacheView(image_view);
  gamma=PerceptibleReciprocal(area);
  image->error.mean_error_per_pixel=gamma*mean_error_per_pixel;
  image->error.normalized_mean_error=gamma*QuantumScale*QuantumScale*mean_error;
  image->error.normalized_maximum_error=QuantumScale*maximum_error;
  status=image->error.mean_error_per_pixel == 0.0 ? MagickTrue : MagickFalse;
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S i m i l a r i t y I m a g e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SimilarityImage() compares the reference image of the image and returns the
%  best match offset.  In addition, it returns a similarity image such that an
%  exact match location is completely white and if none of the pixels match,
%  black, otherwise some gray level in-between.
%
%  The format of the SimilarityImageImage method is:
%
%      Image *SimilarityImage(const Image *image,const Image *reference,
%        RectangleInfo *offset,double *similarity,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o reference: find an area of the image that closely resembles this image.
%
%    o the best match offset of the reference image within the image.
%
%    o similarity: the computed similarity between the images.
%
%    o exception: return any errors or warnings in this structure.
%
*/

static double GetSimilarityMetric(const Image *image,const Image *reference,
  const MetricType metric,const ssize_t x_offset,const ssize_t y_offset,
  ExceptionInfo *exception)
{
  double
    distortion;

  Image
    *similarity_image;

  MagickBooleanType
    status;

  RectangleInfo
    geometry;

  SetGeometry(reference,&geometry);
  geometry.x=x_offset;
  geometry.y=y_offset;
  similarity_image=CropImage(image,&geometry,exception);
  if (similarity_image == (Image *) NULL)
    return(0.0);
  distortion=0.0;
  status=GetImageDistortion(similarity_image,reference,metric,&distortion,
    exception);
  (void) status;
  similarity_image=DestroyImage(similarity_image);
  return(distortion);
}

MagickExport Image *SimilarityImage(Image *image,const Image *reference,
  RectangleInfo *offset,double *similarity_metric,ExceptionInfo *exception)
{
  Image
    *similarity_image;

  similarity_image=SimilarityMetricImage(image,reference,
    RootMeanSquaredErrorMetric,offset,similarity_metric,exception);
  return(similarity_image);
}

MagickExport Image *SimilarityMetricImage(Image *image,const Image *reference,
  const MetricType metric,RectangleInfo *offset,double *similarity_metric,
  ExceptionInfo *exception)
{
#define SimilarityImageTag  "Similarity/Image"

  typedef struct
  {     
    double
      similarity;

    ssize_t
      x,
      y;
  } SimilarityInfo;

  CacheView
    *similarity_view;

  const char
    *artifact;

  double
    similarity_threshold;

  Image
    *similarity_image = (Image *) NULL;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  SimilarityInfo
    similarity_info = { MagickMaximumValue, 0, 0 };

  size_t
    rows;

  ssize_t
    y;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  assert(offset != (RectangleInfo *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  SetGeometry(reference,offset);
  *similarity_metric=MagickMaximumValue;
  if (ValidateImageMorphology(image,reference) == MagickFalse)
    ThrowImageException(ImageError,"ImageMorphologyDiffers");
  if ((image->columns < reference->columns) || (image->rows < reference->rows))
    {
      (void) ThrowMagickException(&image->exception,GetMagickModule(),
        OptionWarning,"GeometryDoesNotContainImage","`%s'",image->filename);
      return((Image *) NULL);
    }
  if (metric == PeakAbsoluteErrorMetric)
    {
      (void) ThrowMagickException(&image->exception,GetMagickModule(),
        OptionError,"InvalidUseOfOption","`%s'",image->filename);
      return((Image *) NULL);
    }
  similarity_image=CloneImage(image,image->columns,image->rows,MagickTrue,
    exception);
  if (similarity_image == (Image *) NULL)
    return((Image *) NULL);
  similarity_image->depth=32;
  similarity_image->colorspace=GRAYColorspace;
  similarity_image->matte=MagickFalse;
  status=SetImageStorageClass(similarity_image,DirectClass);
  if (status == MagickFalse)
    {
      InheritException(exception,&similarity_image->exception);
      return(DestroyImage(similarity_image));
    }
  /*
    Measure similarity of reference image against image.
  */
  similarity_threshold=(-1.0);
  artifact=GetImageArtifact(image,"compare:similarity-threshold");
  if (artifact != (const char *) NULL)
    similarity_threshold=StringToDouble(artifact,(char **) NULL);
  status=MagickTrue;
  progress=0;
  similarity_view=AcquireVirtualCacheView(similarity_image,exception);
  rows=similarity_image->rows;
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp declare reduction(similarity:SimilarityInfo: \
    omp_out = omp_out.similarity < omp_in.similarity ? omp_out : omp_in) \
    initializer(omp_priv = {MagickMaximumValue, 0, 0})
  #pragma omp parallel for schedule(static) shared(status) \
    reduction(similarity:similarity_info) 
#endif
  for (y=0; y < (ssize_t) rows; y++)
  {
    double
      similarity;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    if (*similarity_metric <= similarity_threshold)
      continue;
    q=GetCacheViewAuthenticPixels(similarity_view,0,y,similarity_image->columns,
      1,exception);
    if (q == (const PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) similarity_image->columns; x++)
    {
      if (*similarity_metric <= similarity_threshold)
        break;
      similarity=GetSimilarityMetric(image,reference,metric,x,y,exception);
      switch (metric)
      {
        case NormalizedCrossCorrelationErrorMetric: 
        case PeakSignalToNoiseRatioMetric:
        case UndefinedErrorMetric:
        {
          similarity=1.0-similarity;
          break;
        }
        case PerceptualHashErrorMetric:
        {
          similarity=MagickMin(0.01*similarity,1.0);
          break;
        }
        default:
          break;
      }
      if (similarity < similarity_info.similarity)
        {
          similarity_info.similarity=similarity;
          similarity_info.x=x;
          similarity_info.y=y;
        }
      if ((metric == PeakSignalToNoiseRatioMetric) &&
          (fabs(similarity) < MagickEpsilon))
        similarity=1.0-similarity;
      switch (metric)
      {
        case AbsoluteErrorMetric:
        case FuzzErrorMetric:
        case MeanAbsoluteErrorMetric:
        case MeanErrorPerPixelMetric:
        case MeanSquaredErrorMetric:
        case NormalizedCrossCorrelationErrorMetric:
        case PeakAbsoluteErrorMetric:
        case PeakSignalToNoiseRatioMetric:
        case PerceptualHashErrorMetric:
        case RootMeanSquaredErrorMetric:
        {
          SetPixelRed(q,ClampToQuantum((double) QuantumRange-QuantumRange*
            similarity));
          break;
        }
        default:
        {
          SetPixelRed(q,ClampToQuantum((double) QuantumRange*similarity));
          break;
        }
      }
      SetPixelGreen(q,GetPixelRed(q));
      SetPixelBlue(q,GetPixelRed(q));
      q++;
    }
    if (SyncCacheViewAuthenticPixels(similarity_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

        progress++;
        proceed=SetImageProgress(image,SimilarityImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  similarity_view=DestroyCacheView(similarity_view);
  *similarity_metric=similarity_info.similarity;
  offset->x=similarity_info.x;
  offset->y=similarity_info.y;
  if (status == MagickFalse)
    similarity_image=DestroyImage(similarity_image);
  return(similarity_image);
}
