/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                   V   V  IIIII  SSSSS  U   U   AAA   L                      %
%                   V   V    I    SS     U   U  A   A  L                      %
%                   V   V    I     SSS   U   U  AAAAA  L                      %
%                    V V     I       SS  U   U  A   A  L                      %
%                     V    IIIII  SSSSS   UUU   A   A  LLLLL                  %
%                                                                             %
%                EEEEE  FFFFF  FFFFF  EEEEE  CCCC  TTTTT  SSSSS               %
%                E      F      F      E     C        T    SS                  %
%                EEE    FFF    FFF    EEE   C        T     SSS                %
%                E      F      F      E     C        T       SS               %
%                EEEEE  F      F      EEEEE  CCCC    T    SSSSS               %
%                                                                             %
%                                                                             %
%                   MagickCore Image Special Effects Methods                  %
%                                                                             %
%                               Software Design                               %
%                                    Cristy                                   %
%                                 October 1996                                %
%                                                                             %
%                                                                             %
%  Copyright 1999 ImageMagick Studio LLC, a non-profit organization           %
%  dedicated to making software imaging solutions freely available.           %
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
#include "magick/accelerate-private.h"
#include "magick/annotate.h"
#include "magick/artifact.h"
#include "magick/attribute.h"
#include "magick/cache.h"
#include "magick/cache-view.h"
#include "magick/channel.h"
#include "magick/color.h"
#include "magick/color-private.h"
#include "magick/colorspace.h"
#include "magick/colorspace-private.h"
#include "magick/composite.h"
#include "magick/decorate.h"
#include "magick/distort.h"
#include "magick/draw.h"
#include "magick/effect.h"
#include "magick/enhance.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/gem.h"
#include "magick/geometry.h"
#include "magick/layer.h"
#include "magick/list.h"
#include "magick/log.h"
#include "magick/image.h"
#include "magick/image-private.h"
#include "magick/magick.h"
#include "magick/memory_.h"
#include "magick/memory-private.h"
#include "magick/monitor.h"
#include "magick/monitor-private.h"
#include "magick/opencl-private.h"
#include "magick/option.h"
#include "magick/pixel-accessor.h"
#include "magick/pixel-private.h"
#include "magick/property.h"
#include "magick/quantum.h"
#include "magick/quantum-private.h"
#include "magick/random_.h"
#include "magick/random-private.h"
#include "magick/resample.h"
#include "magick/resample-private.h"
#include "magick/resize.h"
#include "magick/resource_.h"
#include "magick/splay-tree.h"
#include "magick/statistic.h"
#include "magick/string_.h"
#include "magick/string-private.h"
#include "magick/thread-private.h"
#include "magick/threshold.h"
#include "magick/transform.h"
#include "magick/utility.h"
#include "magick/visual-effects.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     A d d N o i s e I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AddNoiseImage() adds random noise to the image.
%
%  The format of the AddNoiseImage method is:
%
%      Image *AddNoiseImage(const Image *image,const NoiseType noise_type,
%        ExceptionInfo *exception)
%      Image *AddNoiseImageChannel(const Image *image,const ChannelType channel,
%        const NoiseType noise_type,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o channel: the channel type.
%
%    o noise_type:  The type of noise: Uniform, Gaussian, Multiplicative,
%      Impulse, Laplacian, or Poisson.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *AddNoiseImage(const Image *image,const NoiseType noise_type,
  ExceptionInfo *exception)
{
  Image
    *noise_image;

  noise_image=AddNoiseImageChannel(image,DefaultChannels,noise_type,exception);
  return(noise_image);
}

MagickExport Image *AddNoiseImageChannel(const Image *image,
  const ChannelType channel,const NoiseType noise_type,ExceptionInfo *exception)
{
#define AddNoiseImageTag  "AddNoise/Image"

  CacheView
    *image_view,
    *noise_view;

  const char
    *option;

  double
    attenuate;

  Image
    *noise_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  RandomInfo
    **magick_restrict random_info;

  ssize_t
    y;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
  unsigned long
    key;
#endif

  /*
    Initialize noise image attributes.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
#if defined(MAGICKCORE_OPENCL_SUPPORT)
  noise_image=AccelerateAddNoiseImage(image,channel,noise_type,exception);
  if (noise_image != (Image *) NULL)
    return(noise_image);
#endif
  noise_image=CloneImage(image,0,0,MagickTrue,exception);
  if (noise_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(noise_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&noise_image->exception);
      noise_image=DestroyImage(noise_image);
      return((Image *) NULL);
    }
  /*
    Add noise in each row.
  */
  attenuate=1.0;
  option=GetImageArtifact(image,"attenuate");
  if (option != (char *) NULL)
    attenuate=StringToDouble(option,(char **) NULL);
  status=MagickTrue;
  progress=0;
  random_info=AcquireRandomInfoTLS();
  image_view=AcquireVirtualCacheView(image,exception);
  noise_view=AcquireAuthenticCacheView(noise_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  key=GetRandomSecretKey(random_info[0]);
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,noise_image,image->rows,key == ~0UL)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    const int
      id = GetOpenMPThreadId();

    MagickBooleanType
      sync;

    const IndexPacket
      *magick_restrict indexes;

    const PixelPacket
      *magick_restrict p;

    IndexPacket
      *magick_restrict noise_indexes;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=GetCacheViewAuthenticPixels(noise_view,0,y,noise_image->columns,1,
      exception);
    if ((p == (PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    noise_indexes=GetCacheViewAuthenticIndexQueue(noise_view);
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      if ((channel & RedChannel) != 0)
        SetPixelRed(q,ClampToQuantum(GenerateDifferentialNoise(random_info[id],
          GetPixelRed(p),noise_type,attenuate)));
      if (IsGrayColorspace(image->colorspace) != MagickFalse)
        {
          SetPixelGreen(q,GetPixelRed(q));
          SetPixelBlue(q,GetPixelRed(q));
        }
      else
        {
          if ((channel & GreenChannel) != 0)
            SetPixelGreen(q,ClampToQuantum(GenerateDifferentialNoise(
              random_info[id],GetPixelGreen(p),noise_type,attenuate)));
          if ((channel & BlueChannel) != 0)
            SetPixelBlue(q,ClampToQuantum(GenerateDifferentialNoise(
              random_info[id],GetPixelBlue(p),noise_type,attenuate)));
         }
      if ((channel & OpacityChannel) != 0)
        SetPixelOpacity(q,ClampToQuantum(GenerateDifferentialNoise(
          random_info[id],GetPixelOpacity(p),noise_type,attenuate)));
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace))
        SetPixelIndex(noise_indexes+x,ClampToQuantum(
          GenerateDifferentialNoise(random_info[id],GetPixelIndex(
          indexes+x),noise_type,attenuate)));
      p++;
      q++;
    }
    sync=SyncCacheViewAuthenticPixels(noise_view,exception);
    if (sync == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,AddNoiseImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  noise_view=DestroyCacheView(noise_view);
  image_view=DestroyCacheView(image_view);
  random_info=DestroyRandomInfoTLS(random_info);
  if (status == MagickFalse)
    noise_image=DestroyImage(noise_image);
  return(noise_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     B l u e S h i f t I m a g e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  BlueShiftImage() mutes the colors of the image to simulate a scene at
%  nighttime in the moonlight.
%
%  The format of the BlueShiftImage method is:
%
%      Image *BlueShiftImage(const Image *image,const double factor,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o factor: the shift factor.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *BlueShiftImage(const Image *image,const double factor,
  ExceptionInfo *exception)
{
#define BlueShiftImageTag  "BlueShift/Image"

  CacheView
    *image_view,
    *shift_view;

  Image
    *shift_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  ssize_t
    y;

  /*
    Allocate blue shift image.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  shift_image=CloneImage(image,0,0,MagickTrue,exception);
  if (shift_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(shift_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&shift_image->exception);
      shift_image=DestroyImage(shift_image);
      return((Image *) NULL);
    }
  /*
    Blue-shift DirectClass image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  shift_view=AcquireAuthenticCacheView(shift_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,shift_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    MagickBooleanType
      sync;

    MagickPixelPacket
      pixel;

    Quantum
      quantum;

    const PixelPacket
      *magick_restrict p;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=QueueCacheViewAuthenticPixels(shift_view,0,y,shift_image->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      quantum=GetPixelRed(p);
      if (GetPixelGreen(p) < quantum)
        quantum=GetPixelGreen(p);
      if (GetPixelBlue(p) < quantum)
        quantum=GetPixelBlue(p);
      pixel.red=0.5*((MagickRealType) GetPixelRed(p)+factor*
        (MagickRealType) quantum);
      pixel.green=0.5*((MagickRealType) GetPixelGreen(p)+factor*
        (MagickRealType) quantum);
      pixel.blue=0.5*((MagickRealType) GetPixelBlue(p)+factor*
        (MagickRealType) quantum);
      quantum=GetPixelRed(p);
      if (GetPixelGreen(p) > quantum)
        quantum=GetPixelGreen(p);
      if (GetPixelBlue(p) > quantum)
        quantum=GetPixelBlue(p);
      pixel.red=0.5*((MagickRealType) pixel.red+factor*
        (MagickRealType) quantum);
      pixel.green=0.5*((MagickRealType) pixel.green+factor*
        (MagickRealType) quantum);
      pixel.blue=0.5*((MagickRealType) pixel.blue+factor*
        (MagickRealType) quantum);
      SetPixelRed(q,ClampToQuantum(pixel.red));
      SetPixelGreen(q,ClampToQuantum(pixel.green));
      SetPixelBlue(q,ClampToQuantum(pixel.blue));
      p++;
      q++;
    }
    sync=SyncCacheViewAuthenticPixels(shift_view,exception);
    if (sync == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,BlueShiftImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  image_view=DestroyCacheView(image_view);
  shift_view=DestroyCacheView(shift_view);
  if (status == MagickFalse)
    shift_image=DestroyImage(shift_image);
  return(shift_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     C h a r c o a l I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CharcoalImage() creates a new image that is a copy of an existing one with
%  the edge highlighted.  It allocates the memory necessary for the new Image
%  structure and returns a pointer to the new image.
%
%  The format of the CharcoalImage method is:
%
%      Image *CharcoalImage(const Image *image,const double radius,
%        const double sigma,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o radius: the radius of the pixel neighborhood.
%
%    o sigma: the standard deviation of the Gaussian, in pixels.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *CharcoalImage(const Image *image,const double radius,
  const double sigma,ExceptionInfo *exception)
{
  Image
    *charcoal_image,
    *edge_image;

  MagickBooleanType
    status;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  edge_image=EdgeImage(image,radius,exception);
  if (edge_image == (Image *) NULL)
    return((Image *) NULL);
  charcoal_image=(Image *) NULL;
  status=ClampImage(edge_image);
  if (status != MagickFalse)
    charcoal_image=BlurImage(edge_image,radius,sigma,exception);
  edge_image=DestroyImage(edge_image);
  if (charcoal_image == (Image *) NULL)
    return((Image *) NULL);
  status=NormalizeImage(charcoal_image);
  if (status != MagickFalse)
    status=NegateImage(charcoal_image,MagickFalse);
  if (status != MagickFalse)
    status=GrayscaleImage(charcoal_image,image->intensity);
  if (status == MagickFalse)
    charcoal_image=DestroyImage(charcoal_image);
  return(charcoal_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     C o l o r i z e I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ColorizeImage() blends the fill color with each pixel in the image.
%  A percentage blend is specified with opacity.  Control the application
%  of different color components by specifying a different percentage for
%  each component (e.g. 90/100/10 is 90% red, 100% green, and 10% blue).
%
%  The format of the ColorizeImage method is:
%
%      Image *ColorizeImage(const Image *image,const char *opacity,
%        const PixelPacket colorize,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o opacity:  A character string indicating the level of opacity as a
%      percentage.
%
%    o colorize: A color value.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *ColorizeImage(const Image *image,const char *opacity,
  const PixelPacket colorize,ExceptionInfo *exception)
{
#define ColorizeImageTag  "Colorize/Image"

  CacheView
    *colorize_view,
    *image_view;

  GeometryInfo
    geometry_info;

  Image
    *colorize_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    pixel;

  MagickStatusType
    flags;

  ssize_t
    y;

  /*
    Allocate colorized image.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  colorize_image=CloneImage(image,0,0,MagickTrue,exception);
  if (colorize_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(colorize_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&colorize_image->exception);
      colorize_image=DestroyImage(colorize_image);
      return((Image *) NULL);
    }
  if ((IsGrayColorspace(image->colorspace) != MagickFalse) ||
      (IsPixelGray(&colorize) != MagickFalse))
    (void) SetImageColorspace(colorize_image,sRGBColorspace);
  if ((colorize_image->matte == MagickFalse) &&
      (colorize.opacity != OpaqueOpacity))
    (void) SetImageAlphaChannel(colorize_image,OpaqueAlphaChannel);
  if (opacity == (const char *) NULL)
    return(colorize_image);
  /*
    Determine RGB values of the pen color.
  */
  flags=ParseGeometry(opacity,&geometry_info);
  pixel.red=geometry_info.rho;
  pixel.green=geometry_info.rho;
  pixel.blue=geometry_info.rho;
  pixel.opacity=(MagickRealType) OpaqueOpacity;
  if ((flags & SigmaValue) != 0)
    pixel.green=geometry_info.sigma;
  if ((flags & XiValue) != 0)
    pixel.blue=geometry_info.xi;
  if ((flags & PsiValue) != 0)
    pixel.opacity=geometry_info.psi;
  /*
    Colorize DirectClass image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  colorize_view=AcquireAuthenticCacheView(colorize_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,colorize_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    MagickBooleanType
      sync;

    const PixelPacket
      *magick_restrict p;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=QueueCacheViewAuthenticPixels(colorize_view,0,y,colorize_image->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      SetPixelRed(q,(((MagickRealType) GetPixelRed(p)*(100.0-pixel.red)+
        (MagickRealType) colorize.red*(MagickRealType) pixel.red)/100.0));
      SetPixelGreen(q,(((MagickRealType) GetPixelGreen(p)*(100.0-pixel.green)+
        (MagickRealType) colorize.green*(MagickRealType) pixel.green)/100.0));
      SetPixelBlue(q,(((MagickRealType) GetPixelBlue(p)*(100.0-pixel.blue)+
        (MagickRealType) colorize.blue*(MagickRealType) pixel.blue)/100.0));
      if (colorize_image->matte == MagickFalse)
        SetPixelOpacity(q,GetPixelOpacity(p));
      else
        SetPixelOpacity(q,(((MagickRealType) GetPixelOpacity(p)*(100.0-
          pixel.opacity)+(MagickRealType) colorize.opacity*pixel.opacity)/
          100.0));
      p++;
      q++;
    }
    sync=SyncCacheViewAuthenticPixels(colorize_view,exception);
    if (sync == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,ColorizeImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  image_view=DestroyCacheView(image_view);
  colorize_view=DestroyCacheView(colorize_view);
  if (status == MagickFalse)
    colorize_image=DestroyImage(colorize_image);
  return(colorize_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     C o l o r M a t r i x I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ColorMatrixImage() applies color transformation to an image. This method
%  permits saturation changes, hue rotation, luminance to alpha, and various
%  other effects.  Although variable-sized transformation matrices can be used,
%  typically one uses a 5x5 matrix for an RGBA image and a 6x6 for CMYKA
%  (or RGBA with offsets).  The matrix is similar to those used by Adobe Flash
%  except offsets are in column 6 rather than 5 (in support of CMYKA images)
%  and offsets are normalized (divide Flash offset by 255).
%
%  The format of the ColorMatrixImage method is:
%
%      Image *ColorMatrixImage(const Image *image,
%        const KernelInfo *color_matrix,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o color_matrix:  the color matrix.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *ColorMatrixImage(const Image *image,
  const KernelInfo *color_matrix,ExceptionInfo *exception)
{
#define ColorMatrixImageTag  "ColorMatrix/Image"

  CacheView
    *color_view,
    *image_view;

  double
    ColorMatrix[6][6] =
    {
      { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
      { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
      { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 },
      { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },
      { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },
      { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 }
    };

  Image
    *color_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  ssize_t
    i;

  ssize_t
    u,
    v,
    y;

  /*
    Create color matrix.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  i=0;
  for (v=0; v < (ssize_t) color_matrix->height; v++)
    for (u=0; u < (ssize_t) color_matrix->width; u++)
    {
      if ((v < 6) && (u < 6))
        ColorMatrix[v][u]=color_matrix->values[i];
      i++;
    }
  /*
    Initialize color image.
  */
  color_image=CloneImage(image,0,0,MagickTrue,exception);
  if (color_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(color_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&color_image->exception);
      color_image=DestroyImage(color_image);
      return((Image *) NULL);
    }
  if (image->debug != MagickFalse)
    {
      char
        format[MaxTextExtent],
        *message;

      (void) LogMagickEvent(TransformEvent,GetMagickModule(),
        "  ColorMatrix image with color matrix:");
      message=AcquireString("");
      for (v=0; v < 6; v++)
      {
        *message='\0';
        (void) FormatLocaleString(format,MaxTextExtent,"%.20g: ",(double) v);
        (void) ConcatenateString(&message,format);
        for (u=0; u < 6; u++)
        {
          (void) FormatLocaleString(format,MaxTextExtent,"%+f ",
            ColorMatrix[v][u]);
          (void) ConcatenateString(&message,format);
        }
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),"%s",message);
      }
      message=DestroyString(message);
    }
  /*
    ColorMatrix image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  color_view=AcquireAuthenticCacheView(color_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,color_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    MagickRealType
      pixel;

    const IndexPacket
      *magick_restrict indexes;

    const PixelPacket
      *magick_restrict p;

    ssize_t
      x;

    IndexPacket
      *magick_restrict color_indexes;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=GetCacheViewAuthenticPixels(color_view,0,y,color_image->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    color_indexes=GetCacheViewAuthenticIndexQueue(color_view);
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      ssize_t
        v;

      size_t
        height;

      height=color_matrix->height > 6 ? 6UL : color_matrix->height;
      for (v=0; v < (ssize_t) height; v++)
      {
        pixel=ColorMatrix[v][0]*(MagickRealType) GetPixelRed(p)+
          ColorMatrix[v][1]*(MagickRealType) GetPixelGreen(p)+
          ColorMatrix[v][2]*(MagickRealType) GetPixelBlue(p);
        if (image->matte != MagickFalse)
          pixel+=ColorMatrix[v][3]*((MagickRealType) QuantumRange-
            (MagickRealType) GetPixelOpacity(p));
        if (image->colorspace == CMYKColorspace)
          pixel+=ColorMatrix[v][4]*(MagickRealType) GetPixelIndex(indexes+x);
        pixel+=(MagickRealType) QuantumRange*ColorMatrix[v][5];
        switch (v)
        {
          case 0: SetPixelRed(q,ClampToQuantum(pixel)); break;
          case 1: SetPixelGreen(q,ClampToQuantum(pixel)); break;
          case 2: SetPixelBlue(q,ClampToQuantum(pixel)); break;
          case 3:
          {
            if (image->matte != MagickFalse)
              SetPixelAlpha(q,ClampToQuantum(pixel));
            break;
          }
          case 4:
          {
            if (image->colorspace == CMYKColorspace)
              SetPixelIndex(color_indexes+x,ClampToQuantum(pixel));
            break;
          }
        }
      }
      p++;
      q++;
    }
    if (SyncCacheViewAuthenticPixels(color_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,ColorMatrixImageTag,progress,
          image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  color_view=DestroyCacheView(color_view);
  image_view=DestroyCacheView(image_view);
  if (status == MagickFalse)
    color_image=DestroyImage(color_image);
  return(color_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     I m p l o d e I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ImplodeImage() creates a new image that is a copy of an existing
%  one with the image pixels "implode" by the specified percentage.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ImplodeImage method is:
%
%      Image *ImplodeImage(const Image *image,const double amount,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o implode_image: Method ImplodeImage returns a pointer to the image
%      after it is implode.  A null image is returned if there is a memory
%      shortage.
%
%    o image: the image.
%
%    o amount:  Define the extent of the implosion.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *ImplodeImage(const Image *image,const double amount,
  ExceptionInfo *exception)
{
#define ImplodeImageTag  "Implode/Image"

  CacheView
    *image_view,
    *implode_view;

  double
    radius;

  Image
    *implode_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    zero;

  PointInfo
    center,
    scale;

  ssize_t
    y;

  /*
    Initialize implode image attributes.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  implode_image=CloneImage(image,0,0,MagickTrue,exception);
  if (implode_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(implode_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&implode_image->exception);
      implode_image=DestroyImage(implode_image);
      return((Image *) NULL);
    }
  if (implode_image->background_color.opacity != OpaqueOpacity)
    implode_image->matte=MagickTrue;
  /*
    Compute scaling factor.
  */
  scale.x=1.0;
  scale.y=1.0;
  center.x=0.5*image->columns;
  center.y=0.5*image->rows;
  radius=center.x;
  if (image->columns > image->rows)
    scale.y=(double) image->columns*PerceptibleReciprocal((double)
      image->rows);
  else
    if (image->columns < image->rows)
      {
        scale.x=(double) image->rows*PerceptibleReciprocal((double)
          image->columns);
        radius=center.y;
      }
  /*
    Implode image.
  */
  status=MagickTrue;
  progress=0;
  GetMagickPixelPacket(implode_image,&zero);
  image_view=AcquireVirtualCacheView(image,exception);
  implode_view=AcquireAuthenticCacheView(implode_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,implode_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    double
      distance;

    MagickPixelPacket
      pixel;

    PointInfo
      delta;

    IndexPacket
      *magick_restrict implode_indexes;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(implode_view,0,y,implode_image->columns,1,
      exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    implode_indexes=GetCacheViewAuthenticIndexQueue(implode_view);
    delta.y=scale.y*(double) (y-center.y);
    pixel=zero;
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      /*
        Determine if the pixel is within an ellipse.
      */
      delta.x=scale.x*(double) (x-center.x);
      distance=delta.x*delta.x+delta.y*delta.y;
      if (distance < (radius*radius))
        {
          double
            factor;

          /*
            Implode the pixel.
          */
          factor=1.0;
          if (distance > 0.0)
            factor=pow(sin((double) (MagickPI*sqrt((double) distance)*
              PerceptibleReciprocal(radius)/2)),-amount);
          status=InterpolateMagickPixelPacket(image,image_view,
            UndefinedInterpolatePixel,(double) (factor*delta.x*PerceptibleReciprocal(scale.x)+
            center.x),(double) (factor*delta.y*PerceptibleReciprocal(scale.y)+center.y),&pixel,
            exception);
          if (status == MagickFalse)
            break;
          SetPixelPacket(implode_image,&pixel,q,implode_indexes+x);
        }
      q++;
    }
    if (SyncCacheViewAuthenticPixels(implode_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,ImplodeImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  implode_view=DestroyCacheView(implode_view);
  image_view=DestroyCacheView(image_view);
  if (status == MagickFalse)
    implode_image=DestroyImage(implode_image);
  return(implode_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     M o r p h I m a g e s                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  The MorphImages() method requires a minimum of two images.  The first
%  image is transformed into the second by a number of intervening images
%  as specified by frames.
%
%  The format of the MorphImage method is:
%
%      Image *MorphImages(const Image *image,const size_t number_frames,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o number_frames:  Define the number of in-between image to generate.
%      The more in-between frames, the smoother the morph.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *MorphImages(const Image *image,
  const size_t number_frames,ExceptionInfo *exception)
{
#define MorphImageTag  "Morph/Image"

  double
    alpha,
    beta;

  Image
    *morph_image,
    *morph_images;

  MagickBooleanType
    status;

  MagickOffsetType
    scene;

  const Image
    *next;

  ssize_t
    i;

  ssize_t
    y;

  /*
    Clone first frame in sequence.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  morph_images=CloneImage(image,0,0,MagickTrue,exception);
  if (morph_images == (Image *) NULL)
    return((Image *) NULL);
  if (GetNextImageInList(image) == (Image *) NULL)
    {
      /*
        Morph single image.
      */
      for (i=1; i < (ssize_t) number_frames; i++)
      {
        morph_image=CloneImage(image,0,0,MagickTrue,exception);
        if (morph_image == (Image *) NULL)
          {
            morph_images=DestroyImageList(morph_images);
            return((Image *) NULL);
          }
        AppendImageToList(&morph_images,morph_image);
        if (image->progress_monitor != (MagickProgressMonitor) NULL)
          {
            MagickBooleanType
              proceed;

            proceed=SetImageProgress(image,MorphImageTag,(MagickOffsetType) i,
              number_frames);
            if (proceed == MagickFalse)
              status=MagickFalse;
          }
      }
      return(GetFirstImageInList(morph_images));
    }
  /*
    Morph image sequence.
  */
  status=MagickTrue;
  scene=0;
  next=image;
  for ( ; GetNextImageInList(next) != (Image *) NULL; next=GetNextImageInList(next))
  {
    for (i=0; i < (ssize_t) number_frames; i++)
    {
      CacheView
        *image_view,
        *morph_view;

      beta=(double) (i+1.0)/(double) (number_frames+1.0);
      alpha=1.0-beta;
      morph_image=ResizeImage(next,(size_t) (alpha*next->columns+beta*
        GetNextImageInList(next)->columns+0.5),(size_t) (alpha*
        next->rows+beta*GetNextImageInList(next)->rows+0.5),
        next->filter,next->blur,exception);
      if (morph_image == (Image *) NULL)
        {
          morph_images=DestroyImageList(morph_images);
          return((Image *) NULL);
        }
      if (SetImageStorageClass(morph_image,DirectClass) == MagickFalse)
        {
          InheritException(exception,&morph_image->exception);
          morph_image=DestroyImage(morph_image);
          return((Image *) NULL);
        }
      AppendImageToList(&morph_images,morph_image);
      morph_images=GetLastImageInList(morph_images);
      morph_image=ResizeImage(GetNextImageInList(next),morph_images->columns,
        morph_images->rows,GetNextImageInList(next)->filter,
        GetNextImageInList(next)->blur,exception);
      if (morph_image == (Image *) NULL)
        {
          morph_images=DestroyImageList(morph_images);
          return((Image *) NULL);
        }
      image_view=AcquireVirtualCacheView(morph_image,exception);
      morph_view=AcquireAuthenticCacheView(morph_images,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
      #pragma omp parallel for schedule(static) shared(status) \
        magick_number_threads(morph_image,morph_image,morph_image->rows,1)
#endif
      for (y=0; y < (ssize_t) morph_images->rows; y++)
      {
        MagickBooleanType
          sync;

        const PixelPacket
          *magick_restrict p;

        ssize_t
          x;

        PixelPacket
          *magick_restrict q;

        if (status == MagickFalse)
          continue;
        p=GetCacheViewVirtualPixels(image_view,0,y,morph_image->columns,1,
          exception);
        q=GetCacheViewAuthenticPixels(morph_view,0,y,morph_images->columns,1,
          exception);
        if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
          {
            status=MagickFalse;
            continue;
          }
        for (x=0; x < (ssize_t) morph_images->columns; x++)
        {
          SetPixelRed(q,ClampToQuantum(alpha*(MagickRealType)
            GetPixelRed(q)+beta*(MagickRealType) GetPixelRed(p)));
          SetPixelGreen(q,ClampToQuantum(alpha*(MagickRealType)
            GetPixelGreen(q)+beta*(MagickRealType) GetPixelGreen(p)));
          SetPixelBlue(q,ClampToQuantum(alpha*(MagickRealType)
            GetPixelBlue(q)+beta*(MagickRealType) GetPixelBlue(p)));
          SetPixelOpacity(q,ClampToQuantum(alpha*(MagickRealType)
            GetPixelOpacity(q)+beta*(MagickRealType) GetPixelOpacity(p)));
          p++;
          q++;
        }
        sync=SyncCacheViewAuthenticPixels(morph_view,exception);
        if (sync == MagickFalse)
          status=MagickFalse;
      }
      morph_view=DestroyCacheView(morph_view);
      image_view=DestroyCacheView(image_view);
      morph_image=DestroyImage(morph_image);
    }
    if (i < (ssize_t) number_frames)
      break;
    /*
      Clone last frame in sequence.
    */
    morph_image=CloneImage(GetNextImageInList(next),0,0,MagickTrue,exception);
    if (morph_image == (Image *) NULL)
      {
        morph_images=DestroyImageList(morph_images);
        return((Image *) NULL);
      }
    AppendImageToList(&morph_images,morph_image);
    morph_images=GetLastImageInList(morph_images);
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

        proceed=SetImageProgress(image,MorphImageTag,scene,
          GetImageListLength(image));
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
    scene++;
  }
  if (GetNextImageInList(next) != (Image *) NULL)
    {
      morph_images=DestroyImageList(morph_images);
      return((Image *) NULL);
    }
  return(GetFirstImageInList(morph_images));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     P l a s m a I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  PlasmaImage() initializes an image with plasma fractal values.  The image
%  must be initialized with a base color and the random number generator
%  seeded before this method is called.
%
%  The format of the PlasmaImage method is:
%
%      MagickBooleanType PlasmaImage(Image *image,const SegmentInfo *segment,
%        size_t attenuate,size_t depth)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o segment:   Define the region to apply plasma fractals values.
%
%    o attenuate: Define the plasma attenuation factor.
%
%    o depth: Limit the plasma recursion depth.
%
*/

static inline Quantum PlasmaPixel(RandomInfo *magick_restrict random_info,
  const MagickRealType pixel,const double noise)
{
  MagickRealType
    plasma;

  plasma=pixel+noise*GetPseudoRandomValue(random_info)-noise/2.0;
  return(ClampToQuantum(plasma));
}

MagickExport MagickBooleanType PlasmaImageProxy(Image *image,
  CacheView *image_view,CacheView *u_view,CacheView *v_view,
  RandomInfo *magick_restrict random_info,
  const SegmentInfo *magick_restrict segment,size_t attenuate,size_t depth)
{
  ExceptionInfo
    *exception;

  double
    plasma;

  MagickStatusType
    status;

  PixelPacket
    u,
    v;

  ssize_t
    x,
    x_mid,
    y,
    y_mid;

  if ((fabs(segment->x2-segment->x1) < MagickEpsilon) &&
      (fabs(segment->y2-segment->y1) < MagickEpsilon))
    return(MagickTrue);
  if (depth != 0)
    {
      SegmentInfo
        local_info;

      /*
        Divide the area into quadrants and recurse.
      */
      depth--;
      attenuate++;
      x_mid=CastDoubleToLong(ceil((segment->x1+segment->x2)/2-0.5));
      y_mid=CastDoubleToLong(ceil((segment->y1+segment->y2)/2-0.5));
      local_info=(*segment);
      local_info.x2=(double) x_mid;
      local_info.y2=(double) y_mid;
      status=PlasmaImageProxy(image,image_view,u_view,v_view,random_info,
        &local_info,attenuate,depth);
      local_info=(*segment);
      local_info.y1=(double) y_mid;
      local_info.x2=(double) x_mid;
      status&=PlasmaImageProxy(image,image_view,u_view,v_view,random_info,
        &local_info,attenuate,depth);
      local_info=(*segment);
      local_info.x1=(double) x_mid;
      local_info.y2=(double) y_mid;
      status&=PlasmaImageProxy(image,image_view,u_view,v_view,random_info,
        &local_info,attenuate,depth);
      local_info=(*segment);
      local_info.x1=(double) x_mid;
      local_info.y1=(double) y_mid;
      status&=PlasmaImageProxy(image,image_view,u_view,v_view,random_info,
        &local_info,attenuate,depth);
      return(status == 0 ? MagickFalse : MagickTrue);
    }
  x_mid=CastDoubleToLong(ceil((segment->x1+segment->x2)/2-0.5));
  y_mid=CastDoubleToLong(ceil((segment->y1+segment->y2)/2-0.5));
  if ((fabs(segment->x1-x_mid) < MagickEpsilon) &&
      (fabs(segment->x2-x_mid) < MagickEpsilon) &&
      (fabs(segment->y1-y_mid) < MagickEpsilon) &&
      (fabs(segment->y2-y_mid) < MagickEpsilon))
    return(MagickFalse);
  /*
    Average pixels and apply plasma.
  */
  status=MagickTrue;
  exception=(&image->exception);
  plasma=(double) QuantumRange/(2.0*attenuate);
  if ((fabs(segment->x1-x_mid) >= MagickEpsilon) ||
      (fabs(segment->x2-x_mid) >= MagickEpsilon))
    {
      PixelPacket
        *magick_restrict q;

      /*
        Left pixel.
      */
      x=CastDoubleToLong(ceil(segment->x1-0.5));
      (void) GetOneCacheViewVirtualPixel(u_view,x,CastDoubleToLong(ceil(
        segment->y1-0.5)),&u,exception);
      (void) GetOneCacheViewVirtualPixel(v_view,x,CastDoubleToLong(ceil(
        segment->y2-0.5)),&v,exception);
      q=QueueCacheViewAuthenticPixels(image_view,x,y_mid,1,1,exception);
      if (q == (PixelPacket *) NULL)
        return(MagickTrue);
      SetPixelRed(q,PlasmaPixel(random_info,((MagickRealType) u.red+
        (MagickRealType) v.red)/2.0,plasma));
      SetPixelGreen(q,PlasmaPixel(random_info,((MagickRealType) u.green+
        (MagickRealType) v.green)/2.0,plasma));
      SetPixelBlue(q,PlasmaPixel(random_info,((MagickRealType) u.blue+
        (MagickRealType) v.blue)/2.0,plasma));
      status=SyncCacheViewAuthenticPixels(image_view,exception);
      if (fabs(segment->x1-segment->x2) >= MagickEpsilon)
        {
          /*
            Right pixel.
          */
          x=CastDoubleToLong(ceil(segment->x2-0.5));
          (void) GetOneCacheViewVirtualPixel(u_view,x,CastDoubleToLong(ceil(
            segment->y1-0.5)),&u,exception);
          (void) GetOneCacheViewVirtualPixel(v_view,x,CastDoubleToLong(ceil(
            segment->y2-0.5)),&v,exception);
          q=QueueCacheViewAuthenticPixels(image_view,x,y_mid,1,1,exception);
          if (q == (PixelPacket *) NULL)
            return(MagickFalse);
          SetPixelRed(q,PlasmaPixel(random_info,((MagickRealType) u.red+
            (MagickRealType) v.red)/2.0,plasma));
          SetPixelGreen(q,PlasmaPixel(random_info,((MagickRealType) u.green+
            (MagickRealType) v.green)/2.0,plasma));
          SetPixelBlue(q,PlasmaPixel(random_info,((MagickRealType) u.blue+
            (MagickRealType) v.blue)/2.0,plasma));
          status=SyncCacheViewAuthenticPixels(image_view,exception);
        }
    }
  if ((fabs(segment->y1-y_mid) >= MagickEpsilon) ||
      (fabs(segment->y2-y_mid) >= MagickEpsilon))
    {
      if ((fabs(segment->x1-x_mid) >= MagickEpsilon) ||
          (fabs(segment->y2-y_mid) >= MagickEpsilon))
        {
          PixelPacket
            *magick_restrict q;

          /*
            Bottom pixel.
          */
          y=CastDoubleToLong(ceil(segment->y2-0.5));
          (void) GetOneCacheViewVirtualPixel(u_view,CastDoubleToLong(ceil(
            segment->x1-0.5)),y,&u,exception);
          (void) GetOneCacheViewVirtualPixel(v_view,CastDoubleToLong(ceil(
            segment->x2-0.5)),y,&v,exception);
          q=QueueCacheViewAuthenticPixels(image_view,x_mid,y,1,1,exception);
          if (q == (PixelPacket *) NULL)
            return(MagickTrue);
          SetPixelRed(q,PlasmaPixel(random_info,((MagickRealType) u.red+
            (MagickRealType) v.red)/2.0,plasma));
          SetPixelGreen(q,PlasmaPixel(random_info,((MagickRealType) u.green+
            (MagickRealType) v.green)/2.0,plasma));
          SetPixelBlue(q,PlasmaPixel(random_info,((MagickRealType) u.blue+
            (MagickRealType) v.blue)/2.0,plasma));
          status=SyncCacheViewAuthenticPixels(image_view,exception);
        }
      if (fabs(segment->y1-segment->y2) >= MagickEpsilon)
        {
          PixelPacket
            *magick_restrict q;

          /*
            Top pixel.
          */
          y=CastDoubleToLong(ceil(segment->y1-0.5));
          (void) GetOneCacheViewVirtualPixel(u_view,CastDoubleToLong(ceil(
            segment->x1-0.5)),y,&u,exception);
          (void) GetOneCacheViewVirtualPixel(v_view,CastDoubleToLong(ceil(
            segment->x2-0.5)),y,&v,exception);
          q=QueueCacheViewAuthenticPixels(image_view,x_mid,y,1,1,exception);
          if (q == (PixelPacket *) NULL)
            return(MagickTrue);
          SetPixelRed(q,PlasmaPixel(random_info,((MagickRealType) u.red+
            (MagickRealType) v.red)/2.0,plasma));
          SetPixelGreen(q,PlasmaPixel(random_info,((MagickRealType) u.green+
            (MagickRealType) v.green)/2.0,plasma));
          SetPixelBlue(q,PlasmaPixel(random_info,((MagickRealType) u.blue+
            (MagickRealType) v.blue)/2.0,plasma));
          status=SyncCacheViewAuthenticPixels(image_view,exception);
        }
    }
  if ((fabs(segment->x1-segment->x2) >= MagickEpsilon) ||
      (fabs(segment->y1-segment->y2) >= MagickEpsilon))
    {
      PixelPacket
        *magick_restrict q;

      /*
        Middle pixel.
      */
      x=CastDoubleToLong(ceil(segment->x1-0.5));
      y=CastDoubleToLong(ceil(segment->y1-0.5));
      (void) GetOneCacheViewVirtualPixel(u_view,x,y,&u,exception);
      x=CastDoubleToLong(ceil(segment->x2-0.5));
      y=CastDoubleToLong(ceil(segment->y2-0.5));
      (void) GetOneCacheViewVirtualPixel(v_view,x,y,&v,exception);
      q=QueueCacheViewAuthenticPixels(image_view,x_mid,y_mid,1,1,exception);
      if (q == (PixelPacket *) NULL)
        return(MagickTrue);
      SetPixelRed(q,PlasmaPixel(random_info,((MagickRealType) u.red+
        (MagickRealType) v.red)/2.0,plasma));
      SetPixelGreen(q,PlasmaPixel(random_info,((MagickRealType) u.green+
        (MagickRealType) v.green)/2.0,plasma));
      SetPixelBlue(q,PlasmaPixel(random_info,((MagickRealType) u.blue+
        (MagickRealType) v.blue)/2.0,plasma));
      status=SyncCacheViewAuthenticPixels(image_view,exception);
    }
  if ((fabs(segment->x2-segment->x1) < 3.0) &&
      (fabs(segment->y2-segment->y1) < 3.0))
    return(status == 0 ? MagickFalse : MagickTrue);
  return(MagickFalse);
}

MagickExport MagickBooleanType PlasmaImage(Image *image,
  const SegmentInfo *segment,size_t attenuate,size_t depth)
{
  CacheView
    *image_view,
    *u_view,
    *v_view;

  MagickBooleanType
    status;

  RandomInfo
    *random_info;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  if (SetImageStorageClass(image,DirectClass) == MagickFalse)
    return(MagickFalse);
  image_view=AcquireAuthenticCacheView(image,&image->exception);
  u_view=AcquireVirtualCacheView(image,&image->exception);
  v_view=AcquireVirtualCacheView(image,&image->exception);
  random_info=AcquireRandomInfo();
  status=PlasmaImageProxy(image,image_view,u_view,v_view,random_info,segment,
    attenuate,depth);
  random_info=DestroyRandomInfo(random_info);
  v_view=DestroyCacheView(v_view);
  u_view=DestroyCacheView(u_view);
  image_view=DestroyCacheView(image_view);
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   P o l a r o i d I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  PolaroidImage() simulates a Polaroid picture.
%
%  The format of the AnnotateImage method is:
%
%      Image *PolaroidImage(const Image *image,const DrawInfo *draw_info,
%        const double angle,ExceptionInfo exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o draw_info: the draw info.
%
%    o angle: Apply the effect along this angle.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *PolaroidImage(const Image *image,const DrawInfo *draw_info,
  const double angle,ExceptionInfo *exception)
{
  const char
    *value;

  Image
    *bend_image,
    *caption_image,
    *flop_image,
    *picture_image,
    *polaroid_image,
    *rotate_image,
    *trim_image;

  size_t
    height;

  ssize_t
    quantum;

  /*
    Simulate a Polaroid picture.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  quantum=(ssize_t) MagickMax(MagickMax((double) image->columns,(double)
    image->rows)/25.0,10.0);
  height=image->rows+2*quantum;
  caption_image=(Image *) NULL;
  value=GetImageProperty(image,"Caption");
  if (value != (const char *) NULL)
    {
      char
        *caption;

      /*
        Generate caption image.
      */
      caption_image=CloneImage(image,image->columns,1,MagickTrue,exception);
      if (caption_image == (Image *) NULL)
        return((Image *) NULL);
      caption=InterpretImageProperties((ImageInfo *) NULL,(Image *) image,
        value);
      if (caption != (char *) NULL)
        {
          char
            geometry[MaxTextExtent];

          DrawInfo
            *annotate_info;

          MagickBooleanType
            status;

          ssize_t
            count;

          TypeMetric
            metrics;

          annotate_info=CloneDrawInfo((const ImageInfo *) NULL,draw_info);
          (void) CloneString(&annotate_info->text,caption);
          count=FormatMagickCaption(caption_image,annotate_info,MagickTrue,
            &metrics,&caption);
          status=SetImageExtent(caption_image,image->columns,(size_t)
            ((count+1)*(metrics.ascent-metrics.descent)+0.5));
          if (status == MagickFalse)
            caption_image=DestroyImage(caption_image);
          else
            {
              caption_image->background_color=image->border_color;
              (void) SetImageBackgroundColor(caption_image);
              (void) CloneString(&annotate_info->text,caption);
              (void) FormatLocaleString(geometry,MaxTextExtent,"+0+%.20g",
                metrics.ascent);
              if (annotate_info->gravity == UndefinedGravity)
                (void) CloneString(&annotate_info->geometry,AcquireString(
                  geometry));
              (void) AnnotateImage(caption_image,annotate_info);
              height+=caption_image->rows;
            }
          annotate_info=DestroyDrawInfo(annotate_info);
          caption=DestroyString(caption);
        }
    }
  picture_image=CloneImage(image,image->columns+2*quantum,height,MagickTrue,
    exception);
  if (picture_image == (Image *) NULL)
    {
      if (caption_image != (Image *) NULL)
        caption_image=DestroyImage(caption_image);
      return((Image *) NULL);
    }
  picture_image->background_color=image->border_color;
  (void) SetImageBackgroundColor(picture_image);
  (void) CompositeImage(picture_image,OverCompositeOp,image,quantum,quantum);
  if (caption_image != (Image *) NULL)
    {
      (void) CompositeImage(picture_image,OverCompositeOp,caption_image,
        quantum,(ssize_t) (image->rows+3*quantum/2));
      caption_image=DestroyImage(caption_image);
    }
  (void) QueryColorDatabase("none",&picture_image->background_color,exception);
  (void) SetImageAlphaChannel(picture_image,OpaqueAlphaChannel);
  rotate_image=RotateImage(picture_image,90.0,exception);
  picture_image=DestroyImage(picture_image);
  if (rotate_image == (Image *) NULL)
    return((Image *) NULL);
  picture_image=rotate_image;
  bend_image=WaveImage(picture_image,0.01*picture_image->rows,2.0*
    picture_image->columns,exception);
  picture_image=DestroyImage(picture_image);
  if (bend_image == (Image *) NULL)
    return((Image *) NULL);
  InheritException(&bend_image->exception,exception);
  picture_image=bend_image;
  rotate_image=RotateImage(picture_image,-90.0,exception);
  picture_image=DestroyImage(picture_image);
  if (rotate_image == (Image *) NULL)
    return((Image *) NULL);
  picture_image=rotate_image;
  picture_image->background_color=image->background_color;
  polaroid_image=ShadowImage(picture_image,80.0,2.0,quantum/3,quantum/3,
    exception);
  if (polaroid_image == (Image *) NULL)
    {
      picture_image=DestroyImage(picture_image);
      return(picture_image);
    }
  flop_image=FlopImage(polaroid_image,exception);
  polaroid_image=DestroyImage(polaroid_image);
  if (flop_image == (Image *) NULL)
    {
      picture_image=DestroyImage(picture_image);
      return(picture_image);
    }
  polaroid_image=flop_image;
  (void) CompositeImage(polaroid_image,OverCompositeOp,picture_image,
    (ssize_t) (-0.01*picture_image->columns/2.0),0L);
  picture_image=DestroyImage(picture_image);
  (void) QueryColorDatabase("none",&polaroid_image->background_color,exception);
  rotate_image=RotateImage(polaroid_image,angle,exception);
  polaroid_image=DestroyImage(polaroid_image);
  if (rotate_image == (Image *) NULL)
    return((Image *) NULL);
  polaroid_image=rotate_image;
  trim_image=TrimImage(polaroid_image,exception);
  polaroid_image=DestroyImage(polaroid_image);
  if (trim_image == (Image *) NULL)
    return((Image *) NULL);
  polaroid_image=trim_image;
  return(polaroid_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     S e p i a T o n e I m a g e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  MagickSepiaToneImage() applies a special effect to the image, similar to the
%  effect achieved in a photo darkroom by sepia toning.  Threshold ranges from
%  0 to QuantumRange and is a measure of the extent of the sepia toning.  A
%  threshold of 80% is a good starting point for a reasonable tone.
%
%  The format of the SepiaToneImage method is:
%
%      Image *SepiaToneImage(const Image *image,const double threshold,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o threshold: the tone threshold.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *SepiaToneImage(const Image *image,const double threshold,
  ExceptionInfo *exception)
{
#define SepiaToneImageTag  "SepiaTone/Image"

  CacheView
    *image_view,
    *sepia_view;

  Image
    *sepia_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  ssize_t
    y;

  /*
    Initialize sepia-toned image attributes.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  sepia_image=CloneImage(image,0,0,MagickTrue,exception);
  if (sepia_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(sepia_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&sepia_image->exception);
      sepia_image=DestroyImage(sepia_image);
      return((Image *) NULL);
    }
  /*
    Tone each row of the image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  sepia_view=AcquireAuthenticCacheView(sepia_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,sepia_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    const PixelPacket
      *magick_restrict p;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=QueueCacheViewAuthenticPixels(sepia_view,0,y,sepia_image->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      double
        intensity,
        tone;

      intensity=GetPixelIntensity(image,p);
      tone=intensity > threshold ? (double) QuantumRange : intensity+
        (double) QuantumRange-threshold;
      SetPixelRed(q,ClampToQuantum(tone));
      tone=intensity > (7.0*threshold/6.0) ? (double) QuantumRange :
        intensity+(double) QuantumRange-7.0*threshold/6.0;
      SetPixelGreen(q,ClampToQuantum(tone));
      tone=intensity < (threshold/6.0) ? 0 : intensity-threshold/6.0;
      SetPixelBlue(q,ClampToQuantum(tone));
      tone=threshold/7.0;
      if ((double) GetPixelGreen(q) < tone)
        SetPixelGreen(q,ClampToQuantum(tone));
      if ((double) GetPixelBlue(q) < tone)
        SetPixelBlue(q,ClampToQuantum(tone));
      SetPixelOpacity(q,GetPixelOpacity(p));
      p++;
      q++;
    }
    if (SyncCacheViewAuthenticPixels(sepia_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,SepiaToneImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  sepia_view=DestroyCacheView(sepia_view);
  image_view=DestroyCacheView(image_view);
  (void) NormalizeImage(sepia_image);
  (void) ContrastImage(sepia_image,MagickTrue);
  if (status == MagickFalse)
    sepia_image=DestroyImage(sepia_image);
  return(sepia_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     S h a d o w I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ShadowImage() simulates a shadow from the specified image and returns it.
%
%  The format of the ShadowImage method is:
%
%      Image *ShadowImage(const Image *image,const double opacity,
%        const double sigma,const ssize_t x_offset,const ssize_t y_offset,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o opacity: percentage transparency.
%
%    o sigma: the standard deviation of the Gaussian, in pixels.
%
%    o x_offset: the shadow x-offset.
%
%    o y_offset: the shadow y-offset.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *ShadowImage(const Image *image,const double opacity,
  const double sigma,const ssize_t x_offset,const ssize_t y_offset,
  ExceptionInfo *exception)
{
#define ShadowImageTag  "Shadow/Image"

  CacheView
    *image_view;

  Image
    *border_image,
    *clone_image,
    *shadow_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  RectangleInfo
    border_info;

  ssize_t
    y;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  clone_image=CloneImage(image,0,0,MagickTrue,exception);
  if (clone_image == (Image *) NULL)
    return((Image *) NULL);
  if (IsGrayColorspace(image->colorspace) != MagickFalse)
    (void) SetImageColorspace(clone_image,sRGBColorspace);
  (void) SetImageVirtualPixelMethod(clone_image,EdgeVirtualPixelMethod);
  clone_image->compose=OverCompositeOp;
  border_info.width=CastDoubleToUnsigned(2.0*sigma+0.5);
  border_info.height=CastDoubleToUnsigned(2.0*sigma+0.5);
  border_info.x=0;
  border_info.y=0;
  (void) QueryColorDatabase("none",&clone_image->border_color,exception);
  border_image=BorderImage(clone_image,&border_info,exception);
  clone_image=DestroyImage(clone_image);
  if (border_image == (Image *) NULL)
    return((Image *) NULL);
  if (border_image->matte == MagickFalse)
    (void) SetImageAlphaChannel(border_image,OpaqueAlphaChannel);
  /*
    Shadow image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireAuthenticCacheView(border_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(border_image,border_image,border_image->rows,1)
#endif
  for (y=0; y < (ssize_t) border_image->rows; y++)
  {
    PixelPacket
      *magick_restrict q;

    ssize_t
      x;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(image_view,0,y,border_image->columns,1,
      exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) border_image->columns; x++)
    {
      SetPixelRed(q,border_image->background_color.red);
      SetPixelGreen(q,border_image->background_color.green);
      SetPixelBlue(q,border_image->background_color.blue);
      if (border_image->matte == MagickFalse)
        SetPixelOpacity(q,border_image->background_color.opacity);
      else
        SetPixelOpacity(q,ClampToQuantum((MagickRealType) QuantumRange-
          GetPixelAlpha(q)*opacity/100.0));
      q++;
    }
    if (SyncCacheViewAuthenticPixels(image_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,ShadowImageTag,progress,
          border_image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  image_view=DestroyCacheView(image_view);
  shadow_image=BlurImageChannel(border_image,AlphaChannel,0.0,sigma,exception);
  border_image=DestroyImage(border_image);
  if (shadow_image == (Image *) NULL)
    return((Image *) NULL);
  if (shadow_image->page.width == 0)
    shadow_image->page.width=shadow_image->columns;
  if (shadow_image->page.height == 0)
    shadow_image->page.height=shadow_image->rows;
  shadow_image->page.width+=x_offset-(ssize_t) border_info.width;
  shadow_image->page.height+=y_offset-(ssize_t) border_info.height;
  shadow_image->page.x+=x_offset-(ssize_t) border_info.width;
  shadow_image->page.y+=y_offset-(ssize_t) border_info.height;
  return(shadow_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     S k e t c h I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SketchImage() simulates a pencil sketch.  We convolve the image with a
%  Gaussian operator of the given radius and standard deviation (sigma).  For
%  reasonable results, radius should be larger than sigma.  Use a radius of 0
%  and SketchImage() selects a suitable radius for you.  Angle gives the angle
%  of the sketch.
%
%  The format of the SketchImage method is:
%
%    Image *SketchImage(const Image *image,const double radius,
%      const double sigma,const double angle,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o radius: the radius of the Gaussian, in pixels, not counting
%      the center pixel.
%
%    o sigma: the standard deviation of the Gaussian, in pixels.
%
%    o angle: Apply the effect along this angle.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *SketchImage(const Image *image,const double radius,
  const double sigma,const double angle,ExceptionInfo *exception)
{
  CacheView
    *random_view;

  Image
    *blend_image,
    *blur_image,
    *dodge_image,
    *random_image,
    *sketch_image;

  MagickBooleanType
    status;

  MagickPixelPacket
    zero;

  RandomInfo
    **magick_restrict random_info;

  ssize_t
    y;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
  unsigned long
    key;
#endif

  /*
    Sketch image.
  */
  random_image=CloneImage(image,image->columns << 1,image->rows << 1,
    MagickTrue,exception);
  if (random_image == (Image *) NULL)
    return((Image *) NULL);
  status=MagickTrue;
  GetMagickPixelPacket(random_image,&zero);
  random_info=AcquireRandomInfoTLS();
  random_view=AcquireAuthenticCacheView(random_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  key=GetRandomSecretKey(random_info[0]);
#pragma omp parallel for schedule(static) shared(status) \
magick_number_threads(random_image,random_image,random_image->rows,key == ~0UL)
#endif
  for (y=0; y < (ssize_t) random_image->rows; y++)
  {
    const int
      id = GetOpenMPThreadId();

    MagickPixelPacket
      pixel;

    IndexPacket
      *magick_restrict indexes;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=QueueCacheViewAuthenticPixels(random_view,0,y,random_image->columns,1,
      exception);
    if (q == (PixelPacket *) NULL)
    {
      status=MagickFalse;
      continue;
    }
    indexes=GetCacheViewAuthenticIndexQueue(random_view);
    pixel=zero;
    for (x=0; x < (ssize_t) random_image->columns; x++)
    {
      pixel.red=(MagickRealType) QuantumRange*
        GetPseudoRandomValue(random_info[id]);
      pixel.green=pixel.red;
      pixel.blue=pixel.red;
      if (image->colorspace == CMYKColorspace)
        pixel.index=pixel.red;
      SetPixelPacket(random_image,&pixel,q,indexes+x);
      q++;
    }
    if (SyncCacheViewAuthenticPixels(random_view,exception) == MagickFalse)
      status=MagickFalse;
  }
  random_info=DestroyRandomInfoTLS(random_info);
  if (status == MagickFalse)
    {
      random_view=DestroyCacheView(random_view);
      random_image=DestroyImage(random_image);
      return(random_image);
    }
  random_view=DestroyCacheView(random_view);

  blur_image=MotionBlurImage(random_image,radius,sigma,angle,exception);
  random_image=DestroyImage(random_image);
  if (blur_image == (Image *) NULL)
    return((Image *) NULL);
  dodge_image=EdgeImage(blur_image,radius,exception);
  blur_image=DestroyImage(blur_image);
  if (dodge_image == (Image *) NULL)
    return((Image *) NULL);
  status=ClampImage(dodge_image);
  if (status != MagickFalse)
    status=NormalizeImage(dodge_image);
  if (status != MagickFalse)
    status=NegateImage(dodge_image,MagickFalse);
  if (status != MagickFalse)
    status=TransformImage(&dodge_image,(char *) NULL,"50%");
  sketch_image=CloneImage(image,0,0,MagickTrue,exception);
  if (sketch_image == (Image *) NULL)
    {
      dodge_image=DestroyImage(dodge_image);
      return((Image *) NULL);
    }
  (void) CompositeImage(sketch_image,ColorDodgeCompositeOp,dodge_image,0,0);
  dodge_image=DestroyImage(dodge_image);
  blend_image=CloneImage(image,0,0,MagickTrue,exception);
  if (blend_image == (Image *) NULL)
    {
      sketch_image=DestroyImage(sketch_image);
      return((Image *) NULL);
    }
  (void) SetImageArtifact(blend_image,"compose:args","20x80");
  (void) CompositeImage(sketch_image,BlendCompositeOp,blend_image,0,0);
  blend_image=DestroyImage(blend_image);
  return(sketch_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     S o l a r i z e I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SolarizeImage() applies a special effect to the image, similar to the effect
%  achieved in a photo darkroom by selectively exposing areas of photo
%  sensitive paper to light.  Threshold ranges from 0 to QuantumRange and is a
%  measure of the extent of the solarization.
%
%  The format of the SolarizeImage method is:
%
%      MagickBooleanType SolarizeImage(Image *image,const double threshold)
%      MagickBooleanType SolarizeImageChannel(Image *image,
%        const ChannelType channel,const double threshold,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o channel: the channel type.
%
%    o threshold:  Define the extent of the solarization.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport MagickBooleanType SolarizeImage(Image *image,
  const double threshold)
{
  MagickBooleanType
    status;

  status=SolarizeImageChannel(image,DefaultChannels,threshold,
    &image->exception);
  return(status);
}

MagickExport MagickBooleanType SolarizeImageChannel(Image *image,
  const ChannelType channel,const double threshold,ExceptionInfo *exception)
{
#define SolarizeImageTag  "Solarize/Image"

  CacheView
    *image_view;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  ssize_t
    y;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (IsGrayColorspace(image->colorspace) != MagickFalse)
    (void) SetImageColorspace(image,sRGBColorspace);
  if (image->storage_class == PseudoClass)
    {
      ssize_t
        i;

      /*
        Solarize colormap.
      */
      for (i=0; i < (ssize_t) image->colors; i++)
      {
        if ((channel & RedChannel) != 0)
          if ((double) image->colormap[i].red > threshold)
            image->colormap[i].red=QuantumRange-image->colormap[i].red;
        if ((channel & GreenChannel) != 0)
          if ((double) image->colormap[i].green > threshold)
            image->colormap[i].green=QuantumRange-image->colormap[i].green;
        if ((channel & BlueChannel) != 0)
          if ((double) image->colormap[i].blue > threshold)
            image->colormap[i].blue=QuantumRange-image->colormap[i].blue;
      }
    }
  /*
    Solarize image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireAuthenticCacheView(image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(image_view,0,y,image->columns,1,
      exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      if ((channel & RedChannel) != 0)
        if ((double) GetPixelRed(q) > threshold)
          SetPixelRed(q,QuantumRange-GetPixelRed(q));
      if ((channel & GreenChannel) != 0)
        if ((double) GetPixelGreen(q) > threshold)
          SetPixelGreen(q,QuantumRange-GetPixelGreen(q));
      if ((channel & BlueChannel) != 0)
        if ((double) GetPixelBlue(q) > threshold)
          SetPixelBlue(q,QuantumRange-GetPixelBlue(q));
      q++;
    }
    if (SyncCacheViewAuthenticPixels(image_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,SolarizeImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  image_view=DestroyCacheView(image_view);
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S t e g a n o I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SteganoImage() hides a digital watermark within the image.  Recover
%  the hidden watermark later to prove that the authenticity of an image.
%  Offset defines the start position within the image to hide the watermark.
%
%  The format of the SteganoImage method is:
%
%      Image *SteganoImage(const Image *image,Image *watermark,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o watermark: the watermark image.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *SteganoImage(const Image *image,const Image *watermark,
  ExceptionInfo *exception)
{
#define GetBit(alpha,i) ((((size_t) (alpha) >> (size_t) (i)) & 0x01) != 0)
#define SetBit(alpha,i,set) (alpha)=(Quantum) ((set) != 0 ? (size_t) (alpha) \
  | (one << (size_t) (i)) : (size_t) (alpha) & ~(one << (size_t) (i)))
#define SteganoImageTag  "Stegano/Image"

  CacheView
    *stegano_view,
    *watermark_view;

  Image
    *stegano_image;

  int
    c;

  MagickBooleanType
    status;

  PixelPacket
    pixel;

  PixelPacket
    *q;

  ssize_t
    x;

  size_t
    depth,
    one;

  ssize_t
    i,
    j,
    k,
    y;

  /*
    Initialize steganographic image attributes.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(watermark != (const Image *) NULL);
  assert(watermark->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  one=1UL;
  stegano_image=CloneImage(image,0,0,MagickTrue,exception);
  if (stegano_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(stegano_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&stegano_image->exception);
      stegano_image=DestroyImage(stegano_image);
      return((Image *) NULL);
    }
  stegano_image->depth=MAGICKCORE_QUANTUM_DEPTH;
  /*
    Hide watermark in low-order bits of image.
  */
  c=0;
  i=0;
  j=0;
  depth=stegano_image->depth;
  k=image->offset;
  status=MagickTrue;
  watermark_view=AcquireVirtualCacheView(watermark,exception);
  stegano_view=AcquireAuthenticCacheView(stegano_image,exception);
  for (i=(ssize_t) depth-1; (i >= 0) && (j < (ssize_t) depth); i--)
  {
    for (y=0; (y < (ssize_t) watermark->rows) && (j < (ssize_t) depth); y++)
    {
      for (x=0; (x < (ssize_t) watermark->columns) && (j < (ssize_t) depth); x++)
      {
        (void) GetOneCacheViewVirtualPixel(watermark_view,x,y,&pixel,exception);
        if ((k/(ssize_t) stegano_image->columns) >= (ssize_t) stegano_image->rows)
          break;
        q=GetCacheViewAuthenticPixels(stegano_view,k % (ssize_t)
          stegano_image->columns,k/(ssize_t) stegano_image->columns,1,1,
          exception);
        if (q == (PixelPacket *) NULL)
          break;
        switch (c)
        {
          case 0:
          {
            SetBit(GetPixelRed(q),j,GetBit(ClampToQuantum(GetPixelIntensity(
              image,&pixel)),i));
            break;
          }
          case 1:
          {
            SetBit(GetPixelGreen(q),j,GetBit(ClampToQuantum(GetPixelIntensity(
              image,&pixel)),i));
            break;
          }
          case 2:
          {
            SetBit(GetPixelBlue(q),j,GetBit(ClampToQuantum(GetPixelIntensity(
              image,&pixel)),i));
            break;
          }
        }
        if (SyncCacheViewAuthenticPixels(stegano_view,exception) == MagickFalse)
          break;
        c++;
        if (c == 3)
          c=0;
        k++;
        if (k == (ssize_t) (stegano_image->columns*stegano_image->columns))
          k=0;
        if (k == image->offset)
          j++;
      }
    }
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

        proceed=SetImageProgress(image,SteganoImageTag,(MagickOffsetType)
          (depth-i),depth);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  stegano_view=DestroyCacheView(stegano_view);
  watermark_view=DestroyCacheView(watermark_view);
  if (stegano_image->storage_class == PseudoClass)
    (void) SyncImage(stegano_image);
  if (status == MagickFalse)
    stegano_image=DestroyImage(stegano_image);
  return(stegano_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S t e r e o A n a g l y p h I m a g e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  StereoAnaglyphImage() combines two images and produces a single image that
%  is the composite of a left and right image of a stereo pair.  Special
%  red-green stereo glasses are required to view this effect.
%
%  The format of the StereoAnaglyphImage method is:
%
%      Image *StereoImage(const Image *left_image,const Image *right_image,
%        ExceptionInfo *exception)
%      Image *StereoAnaglyphImage(const Image *left_image,
%        const Image *right_image,const ssize_t x_offset,const ssize_t y_offset,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o left_image: the left image.
%
%    o right_image: the right image.
%
%    o exception: return any errors or warnings in this structure.
%
%    o x_offset: amount, in pixels, by which the left image is offset to the
%      right of the right image.
%
%    o y_offset: amount, in pixels, by which the left image is offset to the
%      bottom of the right image.
%
%
*/
MagickExport Image *StereoImage(const Image *left_image,
  const Image *right_image,ExceptionInfo *exception)
{
  return(StereoAnaglyphImage(left_image,right_image,0,0,exception));
}

MagickExport Image *StereoAnaglyphImage(const Image *left_image,
  const Image *right_image,const ssize_t x_offset,const ssize_t y_offset,
  ExceptionInfo *exception)
{
#define StereoImageTag  "Stereo/Image"

  const Image
    *image;

  Image
    *stereo_image;

  MagickBooleanType
    status;

  ssize_t
    y;

  assert(left_image != (const Image *) NULL);
  assert(left_image->signature == MagickCoreSignature);
  assert(right_image != (const Image *) NULL);
  assert(right_image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",
      left_image->filename);
  image=left_image;
  if ((left_image->columns != right_image->columns) ||
      (left_image->rows != right_image->rows))
    ThrowImageException(ImageError,"LeftAndRightImageSizesDiffer");
  /*
    Initialize stereo image attributes.
  */
  stereo_image=CloneImage(left_image,left_image->columns,left_image->rows,
    MagickTrue,exception);
  if (stereo_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(stereo_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&stereo_image->exception);
      stereo_image=DestroyImage(stereo_image);
      return((Image *) NULL);
    }
  (void) SetImageColorspace(stereo_image,sRGBColorspace);
  /*
    Copy left image to red channel and right image to blue channel.
  */
  status=MagickTrue;
  for (y=0; y < (ssize_t) stereo_image->rows; y++)
  {
    const PixelPacket
      *magick_restrict p,
      *magick_restrict q;

    ssize_t
      x;

    PixelPacket
      *magick_restrict r;

    p=GetVirtualPixels(left_image,-x_offset,y-y_offset,image->columns,1,
      exception);
    q=GetVirtualPixels(right_image,0,y,right_image->columns,1,exception);
    r=QueueAuthenticPixels(stereo_image,0,y,stereo_image->columns,1,exception);
    if ((p == (PixelPacket *) NULL) || (q == (PixelPacket *) NULL) ||
        (r == (PixelPacket *) NULL))
      break;
    for (x=0; x < (ssize_t) stereo_image->columns; x++)
    {
      SetPixelRed(r,GetPixelRed(p));
      SetPixelGreen(r,GetPixelGreen(q));
      SetPixelBlue(r,GetPixelBlue(q));
      SetPixelOpacity(r,(GetPixelOpacity(p)+q->opacity)/2);
      p++;
      q++;
      r++;
    }
    if (SyncAuthenticPixels(stereo_image,exception) == MagickFalse)
      break;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

        proceed=SetImageProgress(image,StereoImageTag,(MagickOffsetType) y,
          stereo_image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  if (status == MagickFalse)
    stereo_image=DestroyImage(stereo_image);
  return(stereo_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     S w i r l I m a g e                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SwirlImage() swirls the pixels about the center of the image, where
%  degrees indicates the sweep of the arc through which each pixel is moved.
%  You get a more dramatic effect as the degrees move from 1 to 360.
%
%  The format of the SwirlImage method is:
%
%      Image *SwirlImage(const Image *image,double degrees,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o degrees: Define the tightness of the swirling effect.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *SwirlImage(const Image *image,double degrees,
  ExceptionInfo *exception)
{
#define SwirlImageTag  "Swirl/Image"

  CacheView
    *image_view,
    *swirl_view;

  double
    radius;

  Image
    *swirl_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    zero;

  PointInfo
    center,
    scale;

  ssize_t
    y;

  /*
    Initialize swirl image attributes.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  swirl_image=CloneImage(image,0,0,MagickTrue,exception);
  if (swirl_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(swirl_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&swirl_image->exception);
      swirl_image=DestroyImage(swirl_image);
      return((Image *) NULL);
    }
  if (swirl_image->background_color.opacity != OpaqueOpacity)
    swirl_image->matte=MagickTrue;
  /*
    Compute scaling factor.
  */
  center.x=(double) image->columns/2.0;
  center.y=(double) image->rows/2.0;
  radius=MagickMax(center.x,center.y);
  scale.x=1.0;
  scale.y=1.0;
  if (image->columns > image->rows)
    scale.y=(double) image->columns/(double) image->rows;
  else
    if (image->columns < image->rows)
      scale.x=(double) image->rows/(double) image->columns;
  degrees=(double) DegreesToRadians(degrees);
  /*
    Swirl image.
  */
  status=MagickTrue;
  progress=0;
  GetMagickPixelPacket(swirl_image,&zero);
  image_view=AcquireVirtualCacheView(image,exception);
  swirl_view=AcquireAuthenticCacheView(swirl_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,swirl_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    double
      distance;

    MagickPixelPacket
      pixel;

    PointInfo
      delta;

    IndexPacket
      *magick_restrict swirl_indexes;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(swirl_view,0,y,swirl_image->columns,1,
      exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    swirl_indexes=GetCacheViewAuthenticIndexQueue(swirl_view);
    delta.y=scale.y*(double) (y-center.y);
    pixel=zero;
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      /*
        Determine if the pixel is within an ellipse.
      */
      delta.x=scale.x*(double) (x-center.x);
      distance=delta.x*delta.x+delta.y*delta.y;
      if (distance < (radius*radius))
        {
          double
            cosine,
            factor,
            sine;

          /*
            Swirl the pixel.
          */
          factor=1.0-sqrt(distance)/radius;
          sine=sin((double) (degrees*factor*factor));
          cosine=cos((double) (degrees*factor*factor));
          status=InterpolateMagickPixelPacket(image,image_view,
            UndefinedInterpolatePixel,(double) ((cosine*delta.x-sine*delta.y)/
            scale.x+center.x),(double) ((sine*delta.x+cosine*delta.y)/scale.y+
            center.y),&pixel,exception);
          if (status == MagickFalse)
            break;
          SetPixelPacket(swirl_image,&pixel,q,swirl_indexes+x);
        }
      q++;
    }
    if (SyncCacheViewAuthenticPixels(swirl_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,SwirlImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  swirl_view=DestroyCacheView(swirl_view);
  image_view=DestroyCacheView(image_view);
  if (status == MagickFalse)
    swirl_image=DestroyImage(swirl_image);
  return(swirl_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     T i n t I m a g e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  TintImage() applies a color vector to each pixel in the image.  The length
%  of the vector is 0 for black and white and at its maximum for the midtones.
%  The vector weighting function is f(x)=(1-(4.0*((x-0.5)*(x-0.5))))
%
%  The format of the TintImage method is:
%
%      Image *TintImage(const Image *image,const char *opacity,
%        const PixelPacket tint,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o opacity: A color value used for tinting.
%
%    o tint: A color value used for tinting.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *TintImage(const Image *image,const char *opacity,
  const PixelPacket tint,ExceptionInfo *exception)
{
#define TintImageTag  "Tint/Image"

  CacheView
    *image_view,
    *tint_view;

  GeometryInfo
    geometry_info;

  Image
    *tint_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    color_vector,
    pixel;

  MagickStatusType
    flags;

  ssize_t
    y;

  /*
    Allocate tint image.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  tint_image=CloneImage(image,0,0,MagickTrue,exception);
  if (tint_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(tint_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&tint_image->exception);
      tint_image=DestroyImage(tint_image);
      return((Image *) NULL);
    }
  if ((IsGrayColorspace(image->colorspace) != MagickFalse) &&
      (IsPixelGray(&tint) == MagickFalse))
    (void) SetImageColorspace(tint_image,sRGBColorspace);
  if (opacity == (const char *) NULL)
    return(tint_image);
  /*
    Determine RGB values of the tint color.
  */
  flags=ParseGeometry(opacity,&geometry_info);
  pixel.red=geometry_info.rho;
  pixel.green=geometry_info.rho;
  pixel.blue=geometry_info.rho;
  pixel.opacity=(MagickRealType) OpaqueOpacity;
  if ((flags & SigmaValue) != 0)
    pixel.green=geometry_info.sigma;
  if ((flags & XiValue) != 0)
    pixel.blue=geometry_info.xi;
  if ((flags & PsiValue) != 0)
    pixel.opacity=geometry_info.psi;
  color_vector.red=(MagickRealType) pixel.red*(MagickRealType) tint.red/
    100.0-(MagickRealType) PixelPacketIntensity(&tint);
  color_vector.green=(MagickRealType) pixel.green*(MagickRealType) tint.green/
    100.0-(MagickRealType) PixelPacketIntensity(&tint);
  color_vector.blue=(MagickRealType) pixel.blue*(MagickRealType) tint.blue/
    100.0-(MagickRealType) PixelPacketIntensity(&tint);
  /*
    Tint image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  tint_view=AcquireAuthenticCacheView(tint_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,tint_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    const PixelPacket
      *magick_restrict p;

    PixelPacket
      *magick_restrict q;

    ssize_t
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=QueueCacheViewAuthenticPixels(tint_view,0,y,tint_image->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      double
        weight;

      MagickPixelPacket
        pixel;

      weight=QuantumScale*(MagickRealType) GetPixelRed(p)-0.5;
      pixel.red=(MagickRealType) GetPixelRed(p)+color_vector.red*(1.0-(4.0*
        (weight*weight)));
      SetPixelRed(q,ClampToQuantum(pixel.red));
      weight=QuantumScale*(MagickRealType) GetPixelGreen(p)-0.5;
      pixel.green=(MagickRealType) GetPixelGreen(p)+color_vector.green*(1.0-
        (4.0*(weight*weight)));
      SetPixelGreen(q,ClampToQuantum(pixel.green));
      weight=QuantumScale*(MagickRealType) GetPixelBlue(p)-0.5;
      pixel.blue=(MagickRealType) GetPixelBlue(p)+color_vector.blue*(1.0-(4.0*
        (weight*weight)));
      SetPixelBlue(q,ClampToQuantum(pixel.blue));
      SetPixelOpacity(q,GetPixelOpacity(p));
      p++;
      q++;
    }
    if (SyncCacheViewAuthenticPixels(tint_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,TintImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  tint_view=DestroyCacheView(tint_view);
  image_view=DestroyCacheView(image_view);
  if (status == MagickFalse)
    tint_image=DestroyImage(tint_image);
  return(tint_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     V i g n e t t e I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  VignetteImage() softens the edges of the image in vignette style.
%
%  The format of the VignetteImage method is:
%
%      Image *VignetteImage(const Image *image,const double radius,
%        const double sigma,const ssize_t x,const ssize_t y,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o radius: the radius of the pixel neighborhood.
%
%    o sigma: the standard deviation of the Gaussian, in pixels.
%
%    o x, y:  Define the x and y ellipse offset.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *VignetteImage(const Image *image,const double radius,
  const double sigma,const ssize_t x,const ssize_t y,ExceptionInfo *exception)
{
  char
    ellipse[MaxTextExtent];

  DrawInfo
    *draw_info;

  Image
    *blur_image,
    *canvas_image,
    *oval_image,
    *vignette_image;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  canvas_image=CloneImage(image,0,0,MagickTrue,exception);
  if (canvas_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(canvas_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&canvas_image->exception);
      canvas_image=DestroyImage(canvas_image);
      return((Image *) NULL);
    }
  canvas_image->matte=MagickTrue;
  oval_image=CloneImage(canvas_image,canvas_image->columns,canvas_image->rows,
    MagickTrue,exception);
  if (oval_image == (Image *) NULL)
    {
      canvas_image=DestroyImage(canvas_image);
      return((Image *) NULL);
    }
  (void) QueryColorDatabase("#000000",&oval_image->background_color,exception);
  (void) SetImageBackgroundColor(oval_image);
  draw_info=CloneDrawInfo((const ImageInfo *) NULL,(const DrawInfo *) NULL);
  (void) QueryColorDatabase("#ffffff",&draw_info->fill,exception);
  (void) QueryColorDatabase("#ffffff",&draw_info->stroke,exception);
  (void) FormatLocaleString(ellipse,MaxTextExtent,
    "ellipse %g,%g,%g,%g,0.0,360.0",image->columns/2.0,
    image->rows/2.0,image->columns/2.0-x,image->rows/2.0-y);
  draw_info->primitive=AcquireString(ellipse);
  (void) DrawImage(oval_image,draw_info);
  draw_info=DestroyDrawInfo(draw_info);
  blur_image=BlurImage(oval_image,radius,sigma,exception);
  oval_image=DestroyImage(oval_image);
  if (blur_image == (Image *) NULL)
    {
      canvas_image=DestroyImage(canvas_image);
      return((Image *) NULL);
    }
  blur_image->matte=MagickFalse;
  (void) CompositeImage(canvas_image,CopyOpacityCompositeOp,blur_image,0,0);
  blur_image=DestroyImage(blur_image);
  vignette_image=MergeImageLayers(canvas_image,FlattenLayer,exception);
  canvas_image=DestroyImage(canvas_image);
  if (vignette_image != (Image *) NULL)
    (void) TransformImageColorspace(vignette_image,image->colorspace);
  return(vignette_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     W a v e I m a g e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WaveImage() creates a "ripple" effect in the image by shifting the pixels
%  vertically along a sine wave whose amplitude and wavelength is specified
%  by the given parameters.
%
%  The format of the WaveImage method is:
%
%      Image *WaveImage(const Image *image,const double amplitude,
%        const double wave_length,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o amplitude, wave_length:  Define the amplitude and wave length of the
%      sine wave.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *WaveImage(const Image *image,const double amplitude,
  const double wave_length,ExceptionInfo *exception)
{
#define WaveImageTag  "Wave/Image"

  CacheView
    *image_view,
    *wave_view;

  float
    *sine_map;

  Image
    *wave_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    zero;

  ssize_t
    i;

  ssize_t
    y;

  /*
    Initialize wave image attributes.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  wave_image=CloneImage(image,image->columns,(size_t) (image->rows+2.0*
    fabs(amplitude)),MagickTrue,exception);
  if (wave_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(wave_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&wave_image->exception);
      wave_image=DestroyImage(wave_image);
      return((Image *) NULL);
    }
  if (wave_image->background_color.opacity != OpaqueOpacity)
    wave_image->matte=MagickTrue;
  /*
    Allocate sine map.
  */
  sine_map=(float *) AcquireQuantumMemory((size_t) wave_image->columns,
    sizeof(*sine_map));
  if (sine_map == (float *) NULL)
    {
      wave_image=DestroyImage(wave_image);
      ThrowImageException(ResourceLimitError,"MemoryAllocationFailed");
    }
  for (i=0; i < (ssize_t) wave_image->columns; i++)
    sine_map[i]=(float) (fabs(amplitude)+amplitude*sin((double)
      ((2.0*MagickPI*i)*PerceptibleReciprocal(wave_length))));
  /*
    Wave image.
  */
  status=MagickTrue;
  progress=0;
  GetMagickPixelPacket(wave_image,&zero);
  image_view=AcquireVirtualCacheView(image,exception);
  wave_view=AcquireAuthenticCacheView(wave_image,exception);
  (void) SetCacheViewVirtualPixelMethod(image_view,
    BackgroundVirtualPixelMethod);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(progress,status) \
    magick_number_threads(image,wave_image,wave_image->rows,1)
#endif
  for (y=0; y < (ssize_t) wave_image->rows; y++)
  {
    MagickPixelPacket
      pixel;

    IndexPacket
      *magick_restrict indexes;

    PixelPacket
      *magick_restrict q;

    ssize_t
      x;

    if (status == MagickFalse)
      continue;
    q=QueueCacheViewAuthenticPixels(wave_view,0,y,wave_image->columns,1,
      exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewAuthenticIndexQueue(wave_view);
    pixel=zero;
    for (x=0; x < (ssize_t) wave_image->columns; x++)
    {
      status=InterpolateMagickPixelPacket(image,image_view,
        UndefinedInterpolatePixel,(double) x,(double) (y-sine_map[x]),&pixel,
        exception);
      if (status == MagickFalse)
        break;
      SetPixelPacket(wave_image,&pixel,q,indexes+x);
      q++;
    }
    if (SyncCacheViewAuthenticPixels(wave_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,WaveImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  wave_view=DestroyCacheView(wave_view);
  image_view=DestroyCacheView(image_view);
  sine_map=(float *) RelinquishMagickMemory(sine_map);
  if (status == MagickFalse)
    wave_image=DestroyImage(wave_image);
  return(wave_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%     W a v e l e t D e n o i s e I m a g e                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WaveletDenoiseImage() removes noise from the image using a wavelet
%  transform.  The wavelet transform is a fast hierarchical scheme for
%  processing an image using a set of consecutive lowpass and high_pass filters,
%  followed by a decimation.  This results in a decomposition into different
%  scales which can be regarded as different “frequency bands”, determined by
%  the mother wavelet.  Adapted from dcraw.c by David Coffin.
%
%  The format of the WaveletDenoiseImage method is:
%
%      Image *WaveletDenoiseImage(const Image *image,const double threshold,
%        const double softness,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o threshold: set the threshold for smoothing.
%
%    o softness: attenuate the smoothing threshold.
%
%    o exception: return any errors or warnings in this structure.
%
*/

static inline void HatTransform(const float *magick_restrict pixels,
  const size_t stride,const size_t extent,const size_t scale,float *kernel)
{
  const float
    *magick_restrict p,
    *magick_restrict q,
    *magick_restrict r;

  ssize_t
    i;

  p=pixels;
  q=pixels+scale*stride,
  r=pixels+scale*stride;
  for (i=0; i < (ssize_t) scale; i++)
  {
    kernel[i]=0.25f*(*p+(*p)+(*q)+(*r));
    p+=stride;
    q-=stride;
    r+=stride;
  }
  for ( ; i < (ssize_t) (extent-scale); i++)
  {
    kernel[i]=0.25f*(2.0f*(*p)+*(p-scale*stride)+*(p+scale*stride));
    p+=stride;
  }
  q=p-scale*stride;
  r=pixels+stride*(extent-2);
  for ( ; i < (ssize_t) extent; i++)
  {
    kernel[i]=0.25f*(*p+(*p)+(*q)+(*r));
    p+=stride;
    q+=stride;
    r-=stride;
  }
}

MagickExport Image *WaveletDenoiseImage(const Image *image,
  const double threshold,const double softness,ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *noise_view;

  float
    *kernel,
    *pixels;

  Image
    *noise_image;

  MagickBooleanType
    status;

  MagickSizeType
    number_pixels;

  MemoryInfo
    *pixels_info;

  size_t
    max_channels;

  ssize_t
    channel;

  static const double
    noise_levels[]= {
      0.8002, 0.2735, 0.1202, 0.0585, 0.0291, 0.0152, 0.0080, 0.0044 };

  /*
    Initialize noise image attributes.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  noise_image=(Image *) NULL;
#if defined(MAGICKCORE_OPENCL_SUPPORT)
  noise_image=AccelerateWaveletDenoiseImage(image,threshold,exception);
  if (noise_image != (Image *) NULL)
    return(noise_image);
#endif
  noise_image=CloneImage(image,0,0,MagickTrue,exception);
  if (noise_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(noise_image,DirectClass) == MagickFalse)
    {
      noise_image=DestroyImage(noise_image);
      return((Image *) NULL);
    }
  if (AcquireMagickResource(WidthResource,3*image->columns) == MagickFalse)
    ThrowImageException(ResourceLimitError,"MemoryAllocationFailed");
  pixels_info=AcquireVirtualMemory(3*image->columns,image->rows*
    sizeof(*pixels));
  kernel=(float *) AcquireQuantumMemory(MagickMax(image->rows,image->columns)+1,
    GetOpenMPMaximumThreads()*sizeof(*kernel));
  if ((pixels_info == (MemoryInfo *) NULL) || (kernel == (float *) NULL))
    {
      if (kernel != (float *) NULL)
        kernel=(float *) RelinquishMagickMemory(kernel);
      if (pixels_info != (MemoryInfo *) NULL)
        pixels_info=RelinquishVirtualMemory(pixels_info);
      ThrowImageException(ResourceLimitError,"MemoryAllocationFailed");
    }
  pixels=(float *) GetVirtualMemoryBlob(pixels_info);
  status=MagickTrue;
  number_pixels=image->columns*image->rows;
  max_channels=(size_t) (image->colorspace == CMYKColorspace ? 4 : 3);
  image_view=AcquireAuthenticCacheView(image,exception);
  noise_view=AcquireAuthenticCacheView(noise_image,exception);
  for (channel=0; channel < (ssize_t) max_channels; channel++)
  {
    ssize_t
      i;

    size_t
      high_pass,
      low_pass;

    ssize_t
      level,
      y;

    if (status == MagickFalse)
      continue;
    /*
      Copy channel from image to wavelet pixel array.
    */
    i=0;
    for (y=0; y < (ssize_t) image->rows; y++)
    {
      const IndexPacket
        *magick_restrict indexes;

      const PixelPacket
        *magick_restrict p;

      ssize_t
        x;

      p=GetCacheViewAuthenticPixels(image_view,0,y,image->columns,1,exception);
      if (p == (const PixelPacket *) NULL)
        {
          status=MagickFalse;
          break;
        }
      indexes=GetCacheViewVirtualIndexQueue(image_view);
      for (x=0; x < (ssize_t) image->columns; x++)
      {
        switch (channel)
        {
          case 0: pixels[i]=(float) GetPixelRed(p); break;
          case 1: pixels[i]=(float) GetPixelGreen(p); break;
          case 2: pixels[i]=(float) GetPixelBlue(p); break;
          case 3: pixels[i]=(float) indexes[x]; break;
          default: break;
        }
        i++;
        p++;
      }
    }
    /*
      Low pass filter outputs are called approximation kernel & high pass
      filters are referred to as detail kernel. The detail kernel
      have high values in the noisy parts of the signal.
    */
    high_pass=0;
    for (level=0; level < 5; level++)
    {
      double
        magnitude;

      ssize_t
        x,
        y;

      low_pass=(size_t) (number_pixels*((level & 0x01)+1));
#if defined(MAGICKCORE_OPENMP_SUPPORT)
      #pragma omp parallel for schedule(static,1) \
        magick_number_threads(image,image,image->rows,1)
#endif
      for (y=0; y < (ssize_t) image->rows; y++)
      {
        const int
          id = GetOpenMPThreadId();

        float
          *magick_restrict p,
          *magick_restrict q;

        ssize_t
          x;

        p=kernel+id*image->columns;
        q=pixels+y*image->columns;
        HatTransform(q+high_pass,1,image->columns,(size_t) (1UL << level),p);
        q+=low_pass;
        for (x=0; x < (ssize_t) image->columns; x++)
          *q++=(*p++);
      }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
      #pragma omp parallel for schedule(static,1) \
        magick_number_threads(image,image,image->columns,1)
#endif
      for (x=0; x < (ssize_t) image->columns; x++)
      {
        const int
          id = GetOpenMPThreadId();

        float
          *magick_restrict p,
          *magick_restrict q;

        ssize_t
          y;

        p=kernel+id*image->rows;
        q=pixels+x+low_pass;
        HatTransform(q,image->columns,image->rows,(size_t) (1UL << level),p);
        for (y=0; y < (ssize_t) image->rows; y++)
        {
          *q=(*p++);
          q+=image->columns;
        }
      }
      /*
        To threshold, each coefficient is compared to a threshold value and
        attenuated / shrunk by some factor.
      */
      magnitude=threshold*noise_levels[level];
      for (i=0; i < (ssize_t) number_pixels; ++i)
      {
        pixels[high_pass+i]-=pixels[low_pass+i];
        if ((MagickRealType) pixels[high_pass+i] < -magnitude)
          pixels[high_pass+i]+=(float) (magnitude-softness*magnitude);
        else
          if ((MagickRealType) pixels[high_pass+i] > magnitude)
            pixels[high_pass+i]-=(float) (magnitude-softness*magnitude);
          else
            pixels[high_pass+i]*=(float) softness;
        if (high_pass != 0)
          pixels[i]+=pixels[high_pass+i];
      }
      high_pass=low_pass;
    }
    /*
      Reconstruct image from the thresholded wavelet kernel.
    */
    i=0;
    for (y=0; y < (ssize_t) image->rows; y++)
    {
      MagickBooleanType
        sync;

      IndexPacket
        *magick_restrict noise_indexes;

      PixelPacket
        *magick_restrict q;

      ssize_t
        x;

      q=GetCacheViewAuthenticPixels(noise_view,0,y,noise_image->columns,1,
        exception);
      if (q == (PixelPacket *) NULL)
        {
          status=MagickFalse;
          break;
        }
      noise_indexes=GetCacheViewAuthenticIndexQueue(noise_view);
      for (x=0; x < (ssize_t) image->columns; x++)
      {
        float
          pixel;

        pixel=pixels[i]+pixels[low_pass+i];
        switch (channel)
        {
          case 0: SetPixelRed(q,ClampToQuantum(pixel)); break;
          case 1: SetPixelGreen(q,ClampToQuantum(pixel)); break;
          case 2: SetPixelBlue(q,ClampToQuantum(pixel)); break;
          case 3: SetPixelIndex(noise_indexes+x,ClampToQuantum(pixel)); break;
          default: break;
        }
        i++;
        q++;
      }
      sync=SyncCacheViewAuthenticPixels(noise_view,exception);
      if (sync == MagickFalse)
        status=MagickFalse;
    }
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

        proceed=SetImageProgress(image,AddNoiseImageTag,(MagickOffsetType)
          channel,max_channels);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  noise_view=DestroyCacheView(noise_view);
  image_view=DestroyCacheView(image_view);
  kernel=(float *) RelinquishMagickMemory(kernel);
  pixels_info=RelinquishVirtualMemory(pixels_info);
  return(noise_image);
}
