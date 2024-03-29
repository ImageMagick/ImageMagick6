/*
  Copyright 1999 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.
  
  You may not use this file except in compliance with the License.  You may
  obtain a copy of the License at
  
    https://imagemagick.org/script/license.php
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore acceleration methods.
*/
#ifndef MAGICKCORE_ACCELERATE_PRIVATE_H
#define MAGICKCORE_ACCELERATE_PRIVATE_H

#include "magick/morphology.h"
#include "magick/resample.h"
#include "magick/resize.h"
#include "magick/statistic.h"
#include "magick/visual-effects.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#if defined(MAGICKCORE_OPENCL_SUPPORT)

extern MagickPrivate Image
  *AccelerateAddNoiseImage(const Image*,const ChannelType,const NoiseType,
    ExceptionInfo *),
  *AccelerateBlurImage(const Image *,const ChannelType,const double,
    const double,ExceptionInfo *),
  *AccelerateConvolveImageChannel(const Image *,const ChannelType,
    const KernelInfo *,ExceptionInfo *),
  *AccelerateDespeckleImage(const Image *,ExceptionInfo *),
  *AccelerateLocalContrastImage(const Image *,const double,const double,
    ExceptionInfo *),
  *AccelerateMotionBlurImage(const Image*, const ChannelType,
    const double*,const size_t,const OffsetInfo*,ExceptionInfo*),
  *AccelerateRadialBlurImage(const Image *,const ChannelType,const double,
    ExceptionInfo *),
  *AccelerateResizeImage(const Image *,const size_t,const size_t,
    const ResizeFilter *,ExceptionInfo *),
  *AccelerateUnsharpMaskImage(const Image *,const ChannelType,const double,
    const double,const double,const double,ExceptionInfo *),
  *AccelerateWaveletDenoiseImage(const Image *,const double,ExceptionInfo *);

extern MagickPrivate MagickBooleanType
  AccelerateCompositeImage(Image *,const ChannelType,const CompositeOperator,
    const Image *,const ssize_t,const ssize_t,const float,const float,ExceptionInfo *),
  AccelerateContrastImage(Image *,const MagickBooleanType,ExceptionInfo *),
  AccelerateContrastStretchImageChannel(Image *, const ChannelType, const double, const double, 
    ExceptionInfo*),
  AccelerateEqualizeImage(Image *,const ChannelType,ExceptionInfo *),
  AccelerateFunctionImage(Image *,const ChannelType,const MagickFunction,
    const size_t,const double *,ExceptionInfo *),
  AccelerateGrayscaleImage(Image*, const PixelIntensityMethod,
    ExceptionInfo *),
  AccelerateModulateImage(Image*, double, double, double, 
    ColorspaceType, ExceptionInfo*);

#endif

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
