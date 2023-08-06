/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%            DDDD   EEEEE   CCCC   OOO   RRRR    AAA   TTTTT  EEEEE           %
%            D   D  E      C      O   O  R   R  A   A    T    E               %
%            D   D  EEE    C      O   O  RRRR   AAAAA    T    EEE             %
%            D   D  E      C      O   O  R R    A   A    T    E               %
%            DDDD   EEEEE   CCCC   OOO   R  R   A   A    T    EEEEE           %
%                                                                             %
%                                                                             %
%                     MagickCore Image Decoration Methods                     %
%                                                                             %
%                                Software Design                              %
%                                     Cristy                                  %
%                                   July 1992                                 %
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
#include "magick/cache-view.h"
#include "magick/channel.h"
#include "magick/color-private.h"
#include "magick/colorspace-private.h"
#include "magick/composite.h"
#include "magick/decorate.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/image.h"
#include "magick/memory_.h"
#include "magick/monitor.h"
#include "magick/monitor-private.h"
#include "magick/pixel-accessor.h"
#include "magick/pixel-private.h"
#include "magick/quantum.h"
#include "magick/resource_.h"
#include "magick/thread-private.h"
#include "magick/transform.h"

/*
  Define declarations.
*/
#define AccentuateModulate  ((MagickRealType) ScaleCharToQuantum(80))
#define HighlightModulate  ((MagickRealType) ScaleCharToQuantum(125))
#define ShadowModulate  ((MagickRealType) ScaleCharToQuantum(135))
#define DepthModulate  ((MagickRealType) ScaleCharToQuantum(185))
#define TroughModulate  ((MagickRealType) ScaleCharToQuantum(110))

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   B o r d e r I m a g e                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  BorderImage() surrounds the image with a border of the color defined by
%  the bordercolor member of the image structure.  The width and height
%  of the border are defined by the corresponding members of the border_info
%  structure.
%
%  The format of the BorderImage method is:
%
%      Image *BorderImage(const Image *image,const RectangleInfo *border_info,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o border_info:  Define the width and height of the border.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *BorderImage(const Image *image,
  const RectangleInfo *border_info,ExceptionInfo *exception)
{
  Image
    *border_image,
    *clone_image;

  FrameInfo
    frame_info;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(border_info != (RectangleInfo *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  frame_info.width=image->columns+(border_info->width << 1);
  frame_info.height=image->rows+(border_info->height << 1);
  frame_info.x=(ssize_t) border_info->width;
  frame_info.y=(ssize_t) border_info->height;
  frame_info.inner_bevel=0;
  frame_info.outer_bevel=0;
  clone_image=CloneImage(image,0,0,MagickTrue,exception);
  if (clone_image == (Image *) NULL)
    return((Image *) NULL);
  clone_image->matte_color=image->border_color;
  border_image=FrameImage(clone_image,&frame_info,exception);
  clone_image=DestroyImage(clone_image);
  if (border_image != (Image *) NULL)
    border_image->matte_color=image->matte_color;
  return(border_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   F r a m e I m a g e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  FrameImage() adds a simulated three-dimensional border around the image.
%  The color of the border is defined by the matte_color member of image.
%  Members width and height of frame_info specify the border width of the
%  vertical and horizontal sides of the frame.  Members inner and outer
%  indicate the width of the inner and outer shadows of the frame.
%
%  The format of the FrameImage method is:
%
%      Image *FrameImage(const Image *image,const FrameInfo *frame_info,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o frame_info: Define the width and height of the frame and its bevels.
%
%    o exception: return any errors or warnings in this structure.
%
*/
MagickExport Image *FrameImage(const Image *image,const FrameInfo *frame_info,
  ExceptionInfo *exception)
{
#define FrameImageTag  "Frame/Image"

  CacheView
    *image_view,
    *frame_view;

  Image
    *frame_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    accentuate,
    border,
    highlight,
    matte,
    shadow,
    trough;

  ssize_t
    x;

  size_t
    bevel_width,
    height,
    width;

  ssize_t
    y;

  /*
    Check frame geometry.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(frame_info != (FrameInfo *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if ((frame_info->outer_bevel < 0) || (frame_info->inner_bevel < 0))
    ThrowImageException(OptionError,"FrameIsLessThanImageSize");
  bevel_width=(size_t) (frame_info->outer_bevel+frame_info->inner_bevel);
  x=(ssize_t) frame_info->width-frame_info->x-bevel_width;
  y=(ssize_t) frame_info->height-frame_info->y-bevel_width;
  if ((x < (ssize_t) image->columns) || (y < (ssize_t) image->rows))
    ThrowImageException(OptionError,"FrameIsLessThanImageSize");
  /*
    Initialize framed image attributes.
  */
  frame_image=CloneImage(image,frame_info->width,frame_info->height,MagickTrue,
    exception);
  if (frame_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(frame_image,DirectClass) == MagickFalse)
    {
      InheritException(exception,&frame_image->exception);
      frame_image=DestroyImage(frame_image);
      return((Image *) NULL);
    }
  if ((IsPixelGray(&frame_image->border_color) == MagickFalse) &&
      (IsGrayColorspace(frame_image->colorspace) != MagickFalse))
    (void) SetImageColorspace(frame_image,sRGBColorspace);
  if ((frame_image->border_color.opacity != OpaqueOpacity) &&
      (frame_image->matte == MagickFalse))
    (void) SetImageAlphaChannel(frame_image,OpaqueAlphaChannel);
  frame_image->page=image->page;
  if ((image->page.width != 0) && (image->page.height != 0))
    {
      frame_image->page.width+=frame_image->columns-image->columns;
      frame_image->page.height+=frame_image->rows-image->rows;
    }
  /*
    Initialize 3D effects color.
  */
  GetMagickPixelPacket(frame_image,&matte);
  matte.colorspace=sRGBColorspace;
  SetMagickPixelPacket(frame_image,&image->matte_color,(IndexPacket *) NULL,
    &matte);
  GetMagickPixelPacket(frame_image,&border);
  border.colorspace=sRGBColorspace;
  SetMagickPixelPacket(frame_image,&image->border_color,(IndexPacket *) NULL,
    &border);
  GetMagickPixelPacket(frame_image,&accentuate);
  accentuate.red=(MagickRealType) (QuantumScale*(((MagickRealType)
    QuantumRange-(MagickRealType) AccentuateModulate)*matte.red+
    ((MagickRealType) QuantumRange*(MagickRealType) AccentuateModulate)));
  accentuate.green=(MagickRealType) (QuantumScale*(((MagickRealType)
    QuantumRange-(MagickRealType) AccentuateModulate)*matte.green+
    ((MagickRealType) QuantumRange*(MagickRealType) AccentuateModulate)));
  accentuate.blue=(MagickRealType) (QuantumScale*(((MagickRealType)
    QuantumRange-(MagickRealType) AccentuateModulate)*matte.blue+
    ((MagickRealType) QuantumRange*(MagickRealType) AccentuateModulate)));
  accentuate.opacity=matte.opacity;
  GetMagickPixelPacket(frame_image,&highlight);
  highlight.red=(MagickRealType) (QuantumScale*(((MagickRealType)
    QuantumRange-(MagickRealType) HighlightModulate)*matte.red+
    ((MagickRealType) QuantumRange*(MagickRealType) HighlightModulate)));
  highlight.green=(MagickRealType) (QuantumScale*(((MagickRealType)
    QuantumRange-(MagickRealType) HighlightModulate)*matte.green+
    ((MagickRealType) QuantumRange*(MagickRealType) HighlightModulate)));
  highlight.blue=(MagickRealType) (QuantumScale*(((MagickRealType)
    QuantumRange-(MagickRealType) HighlightModulate)*matte.blue+
    ((MagickRealType) QuantumRange*(MagickRealType) HighlightModulate)));
  highlight.opacity=matte.opacity;
  GetMagickPixelPacket(frame_image,&shadow);
  shadow.red=QuantumScale*matte.red*(MagickRealType) ShadowModulate;
  shadow.green=QuantumScale*matte.green*(MagickRealType) ShadowModulate;
  shadow.blue=QuantumScale*matte.blue*(MagickRealType) ShadowModulate;
  shadow.opacity=matte.opacity;
  GetMagickPixelPacket(frame_image,&trough);
  trough.red=QuantumScale*matte.red*(MagickRealType) TroughModulate;
  trough.green=QuantumScale*matte.green*(MagickRealType) TroughModulate;
  trough.blue=QuantumScale*matte.blue*(MagickRealType) TroughModulate;
  trough.opacity=matte.opacity;
  if (image->colorspace == CMYKColorspace)
    {
      ConvertRGBToCMYK(&matte);
      ConvertRGBToCMYK(&border);
      ConvertRGBToCMYK(&accentuate);
      ConvertRGBToCMYK(&highlight);
      ConvertRGBToCMYK(&shadow);
      ConvertRGBToCMYK(&trough);
    }
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  frame_view=AcquireAuthenticCacheView(frame_image,exception);
  height=(size_t) (frame_info->outer_bevel+(frame_info->y-bevel_width)+
    frame_info->inner_bevel);
  if (height != 0)
    {
      IndexPacket
        *magick_restrict frame_indexes;

      ssize_t
        x;

      PixelPacket
        *magick_restrict q;

      /*
        Draw top of ornamental border.
      */
      q=QueueCacheViewAuthenticPixels(frame_view,0,0,frame_image->columns,
        height,exception);
      frame_indexes=GetCacheViewAuthenticIndexQueue(frame_view);
      if (q != (PixelPacket *) NULL)
        {
          /*
            Draw top of ornamental border.
          */
          for (y=0; y < (ssize_t) frame_info->outer_bevel; y++)
          {
            for (x=0; x < (ssize_t) (frame_image->columns-y); x++)
            {
              if (x < y)
                SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              else
                SetPixelPacket(frame_image,&accentuate,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for ( ; x < (ssize_t) frame_image->columns; x++)
            {
              SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              q++;
              frame_indexes++;
            }
          }
          for (y=0; y < (ssize_t) (frame_info->y-bevel_width); y++)
          {
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            width=frame_image->columns-2*frame_info->outer_bevel;
            for (x=0; x < (ssize_t) width; x++)
            {
              SetPixelPacket(frame_image,&matte,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              q++;
              frame_indexes++;
            }
          }
          for (y=0; y < (ssize_t) frame_info->inner_bevel; y++)
          {
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < (ssize_t) (frame_info->x-bevel_width); x++)
            {
              SetPixelPacket(frame_image,&matte,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            width=image->columns+((size_t) frame_info->inner_bevel << 1)-
              y;
            for (x=0; x < (ssize_t) width; x++)
            {
              if (x < y)
                SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              else
                SetPixelPacket(frame_image,&trough,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for ( ; x < (ssize_t) (image->columns+2*frame_info->inner_bevel); x++)
            {
              SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            width=frame_info->width-frame_info->x-image->columns-bevel_width;
            for (x=0; x < (ssize_t) width; x++)
            {
              SetPixelPacket(frame_image,&matte,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              q++;
              frame_indexes++;
            }
          }
          (void) SyncCacheViewAuthenticPixels(frame_view,exception);
        }
    }
  /*
    Draw sides of ornamental border.
  */
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,frame_image,image->rows,1)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    IndexPacket
      *magick_restrict frame_indexes;

    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    /*
      Initialize scanline with matte color.
    */
    if (status == MagickFalse)
      continue;
    q=QueueCacheViewAuthenticPixels(frame_view,0,frame_info->y+y,
      frame_image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    frame_indexes=GetCacheViewAuthenticIndexQueue(frame_view);
    for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
    {
      SetPixelPacket(frame_image,&highlight,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    for (x=0; x < (ssize_t) (frame_info->x-bevel_width); x++)
    {
      SetPixelPacket(frame_image,&matte,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    for (x=0; x < (ssize_t) frame_info->inner_bevel; x++)
    {
      SetPixelPacket(frame_image,&shadow,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    /*
      Set frame interior pixels.
    */
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      SetPixelPacket(frame_image,&border,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    for (x=0; x < (ssize_t) frame_info->inner_bevel; x++)
    {
      SetPixelPacket(frame_image,&highlight,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    width=frame_info->width-frame_info->x-image->columns-bevel_width;
    for (x=0; x < (ssize_t) width; x++)
    {
      SetPixelPacket(frame_image,&matte,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
    {
      SetPixelPacket(frame_image,&shadow,q,frame_indexes);
      q++;
      frame_indexes++;
    }
    if (SyncCacheViewAuthenticPixels(frame_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp atomic
#endif
        progress++;
        proceed=SetImageProgress(image,FrameImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  height=(size_t) (frame_info->inner_bevel+frame_info->height-
    frame_info->y-image->rows-bevel_width+frame_info->outer_bevel);
  if (height != 0)
    {
      IndexPacket
        *magick_restrict frame_indexes;

      ssize_t
        x;

      PixelPacket
        *magick_restrict q;

      /*
        Draw bottom of ornamental border.
      */
      q=QueueCacheViewAuthenticPixels(frame_view,0,(ssize_t) (frame_image->rows-
        height),frame_image->columns,height,exception);
      if (q != (PixelPacket *) NULL)
        {
          /*
            Draw bottom of ornamental border.
          */
          frame_indexes=GetCacheViewAuthenticIndexQueue(frame_view);
          for (y=frame_info->inner_bevel-1; y >= 0; y--)
          {
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < (ssize_t) (frame_info->x-bevel_width); x++)
            {
              SetPixelPacket(frame_image,&matte,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < y; x++)
            {
              SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for ( ; x < (ssize_t) (image->columns+2*frame_info->inner_bevel); x++)
            {
              if (x >= (ssize_t) (image->columns+2*frame_info->inner_bevel-y))
                SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              else
                SetPixelPacket(frame_image,&accentuate,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            width=frame_info->width-frame_info->x-image->columns-bevel_width;
            for (x=0; x < (ssize_t) width; x++)
            {
              SetPixelPacket(frame_image,&matte,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              q++;
              frame_indexes++;
            }
          }
          height=frame_info->height-frame_info->y-image->rows-bevel_width;
          for (y=0; y < (ssize_t) height; y++)
          {
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            width=frame_image->columns-2*frame_info->outer_bevel;
            for (x=0; x < (ssize_t) width; x++)
            {
              SetPixelPacket(frame_image,&matte,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for (x=0; x < (ssize_t) frame_info->outer_bevel; x++)
            {
              SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              q++;
              frame_indexes++;
            }
          }
          for (y=frame_info->outer_bevel-1; y >= 0; y--)
          {
            for (x=0; x < y; x++)
            {
              SetPixelPacket(frame_image,&highlight,q,frame_indexes);
              q++;
              frame_indexes++;
            }
            for ( ; x < (ssize_t) frame_image->columns; x++)
            {
              if (x >= (ssize_t) (frame_image->columns-y))
                SetPixelPacket(frame_image,&shadow,q,frame_indexes);
              else
                SetPixelPacket(frame_image,&trough,q,frame_indexes);
              q++;
              frame_indexes++;
            }
          }
          (void) SyncCacheViewAuthenticPixels(frame_view,exception);
        }
    }
  frame_view=DestroyCacheView(frame_view);
  image_view=DestroyCacheView(image_view);
  x=(ssize_t) (frame_info->outer_bevel+(frame_info->x-bevel_width)+
    frame_info->inner_bevel);
  y=(ssize_t) (frame_info->outer_bevel+(frame_info->y-bevel_width)+
    frame_info->inner_bevel);
  if (status != MagickFalse)
    status=CompositeImage(frame_image,image->compose,image,x,y);
  if (status == MagickFalse)
    frame_image=DestroyImage(frame_image);
  return(frame_image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R a i s e I m a g e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  RaiseImage() creates a simulated three-dimensional button-like effect
%  by lightening and darkening the edges of the image.  Members width and
%  height of raise_info define the width of the vertical and horizontal
%  edge of the effect.
%
%  The format of the RaiseImage method is:
%
%      MagickBooleanType RaiseImage(const Image *image,
%        const RectangleInfo *raise_info,const MagickBooleanType raise)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o raise_info: Define the width and height of the raise area.
%
%    o raise: A value other than zero creates a 3-D raise effect,
%      otherwise it has a lowered effect.
%
*/
MagickExport MagickBooleanType RaiseImage(Image *image,
  const RectangleInfo *raise_info,const MagickBooleanType raise)
{
#define AccentuateFactor  ((MagickRealType) ScaleCharToQuantum(135))
#define HighlightFactor  ((MagickRealType) ScaleCharToQuantum(190))
#define ShadowFactor  ((MagickRealType) ScaleCharToQuantum(190))
#define RaiseImageTag  "Raise/Image"
#define TroughFactor  ((MagickRealType) ScaleCharToQuantum(135))

  CacheView
    *image_view;

  ExceptionInfo
    *exception;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  Quantum
    foreground,
    background;

  ssize_t
    y;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  assert(raise_info != (RectangleInfo *) NULL);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  exception=(&image->exception);
  if ((image->columns <= (raise_info->width << 1)) ||
      (image->rows <= (raise_info->height << 1)))
    ThrowBinaryException(OptionError,"ImageSizeMustExceedBevelWidth",
      image->filename);
  foreground=QuantumRange;
  background=(Quantum) 0;
  if (raise == MagickFalse)
    {
      foreground=(Quantum) 0;
      background=QuantumRange;
    }
  if (SetImageStorageClass(image,DirectClass) == MagickFalse)
    return(MagickFalse);
  /*
    Raise image.
  */
  status=MagickTrue;
  progress=0;
  image_view=AcquireAuthenticCacheView(image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,raise_info->height,1)
#endif
  for (y=0; y < (ssize_t) raise_info->height; y++)
  {
    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(image_view,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < y; x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      q++;
    }
    for ( ; x < (ssize_t) (image->columns-y); x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*AccentuateFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-AccentuateFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*AccentuateFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-AccentuateFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*AccentuateFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-AccentuateFactor))));
      q++;
    }
    for ( ; x < (ssize_t) image->columns; x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
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
        proceed=SetImageProgress(image,RaiseImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,image->rows-2*raise_info->height,1)
#endif
  for (y=(ssize_t) raise_info->height; y < (ssize_t) (image->rows-raise_info->height); y++)
  {
    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(image_view,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) raise_info->width; x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      q++;
    }
    for ( ; x < (ssize_t) (image->columns-raise_info->width); x++)
      q++;
    for ( ; x < (ssize_t) image->columns; x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
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
        proceed=SetImageProgress(image,RaiseImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static) shared(status) \
    magick_number_threads(image,image,image->rows-raise_info->height,1)
#endif
  for (y=(ssize_t) (image->rows-raise_info->height); y < (ssize_t) image->rows; y++)
  {
    ssize_t
      x;

    PixelPacket
      *magick_restrict q;

    if (status == MagickFalse)
      continue;
    q=GetCacheViewAuthenticPixels(image_view,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) (image->rows-y); x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*HighlightFactor+(MagickRealType) foreground*
        ((MagickRealType) QuantumRange-HighlightFactor))));
      q++;
    }
    for ( ; x < (ssize_t) (image->columns-(image->rows-y)); x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*TroughFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-TroughFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*TroughFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-TroughFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*TroughFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-TroughFactor))));
      q++;
    }
    for ( ; x < (ssize_t) image->columns; x++)
    {
      SetPixelRed(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelRed(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
      SetPixelGreen(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelGreen(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
      SetPixelBlue(q,ClampToQuantum(QuantumScale*((MagickRealType)
        GetPixelBlue(q)*ShadowFactor+(MagickRealType) background*
        ((MagickRealType) QuantumRange-ShadowFactor))));
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
        proceed=SetImageProgress(image,RaiseImageTag,progress,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  image_view=DestroyCacheView(image_view);
  return(status);
}
