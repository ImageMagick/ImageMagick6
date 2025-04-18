/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%        CCCC  L      IIIII  PPPP   BBBB    OOO    AAA   RRRR   DDDD          %
%       C      L        I    P   P  B   B  O   O  A   A  R   R  D   D         %
%       C      L        I    PPP    BBBB   O   O  AAAAA  RRRR   D   D         %
%       C      L        I    P      B   B  O   O  A   A  R R    D   D         %
%        CCCC  LLLLL  IIIII  P      BBBB    OOO   A   A  R  R   DDDD          %
%                                                                             %
%                                                                             %
%                        Read/Write Windows Clipboard.                        %
%                                                                             %
%                              Software Design                                %
%                             Leonard Rosenthol                               %
%                                 May 2002                                    %
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
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#if defined(MAGICKCORE_WINGDI32_DELEGATE)
#  if defined(__CYGWIN__)
#    include <windows.h>
#  else
     /* All MinGW needs ... */
#    include "magick/nt-base-private.h"
#    include <wingdi.h>
#  endif
#endif
#include "magick/blob.h"
#include "magick/blob-private.h"
#include "magick/cache.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/image.h"
#include "magick/image-private.h"
#include "magick/list.h"
#include "magick/magick.h"
#include "magick/memory_.h"
#include "magick/nt-feature.h"
#include "magick/pixel-accessor.h"
#include "magick/quantum-private.h"
#include "magick/static.h"
#include "magick/string_.h"
#include "magick/module.h"

#define BMP_HEADER_SIZE 14

/*
  Forward declarations.
*/
#if defined(MAGICKCORE_WINGDI32_DELEGATE)
static MagickBooleanType
  WriteCLIPBOARDImage(const ImageInfo *,Image *);
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d C L I P B O A R D I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadCLIPBOARDImage() reads an image from the system clipboard and returns
%  it.  It allocates the memory necessary for the new Image structure and
%  returns a pointer to the new image.
%
%  The format of the ReadCLIPBOARDImage method is:
%
%      Image *ReadCLIPBOARDImage(const ImageInfo *image_info,
%        ExceptionInfo exception)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o exception: return any errors or warnings in this structure.
%
*/
#if defined(MAGICKCORE_WINGDI32_DELEGATE)
static Image *ReadCLIPBOARDImage(const ImageInfo *image_info,
  ExceptionInfo *exception)
{
  unsigned char
    *p;

  HANDLE
    clip_handle;

  Image
    *image;

  ImageInfo
    *read_info;

  LPVOID
    clip_mem;

  size_t
    clip_size,
    total_size;

  unsigned char
    offset;

  void
    *clip_data;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",
      image_info->filename);
  image=AcquireImage(image_info);
  if (!IsClipboardFormatAvailable(CF_DIB) &&
      !IsClipboardFormatAvailable(CF_DIBV5))
    ThrowReaderException(CoderError,"NoBitmapOnClipboard");
  if (!OpenClipboard(NULL))
    ThrowReaderException(CoderError,"UnableToReadImageData");
  clip_handle=GetClipboardData(CF_DIBV5);
  if (!clip_handle)
    clip_handle=GetClipboardData(CF_DIB);
  if ((clip_handle == NULL) || (clip_handle == INVALID_HANDLE_VALUE))
    {
      CloseClipboard();
      ThrowReaderException(CoderError,"UnableToReadImageData");
    }
  clip_size=(size_t) GlobalSize(clip_handle);
  total_size=clip_size+BMP_HEADER_SIZE;
  clip_data=AcquireMagickMemory(total_size);
  if (clip_data == (void *) NULL)
    {
      CloseClipboard();
      ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
    }
  clip_mem=GlobalLock(clip_handle);
  if (clip_mem == (LPVOID) NULL)
    {
      CloseClipboard();
      clip_data=RelinquishMagickMemory(clip_data);
      ThrowReaderException(CoderError,"UnableToReadImageData");
    }
  p=(unsigned char *) clip_data;
  p+=(ptrdiff_t) BMP_HEADER_SIZE;
  (void) memcpy(p,clip_mem,clip_size);
  (void) GlobalUnlock(clip_mem);
  (void) CloseClipboard();
  memset(clip_data,0,BMP_HEADER_SIZE);
  offset=p[0];
  if ((p[0] == 40) && (p[16] == BI_BITFIELDS))
    offset+=12;
  else
    {
      unsigned int
        image_size;

      image_size=(unsigned int) p[20];
      image_size|=(unsigned int) p[21] << 8;
      image_size|=(unsigned int) p[22] << 16;
      image_size|=(unsigned int) p[23] << 24;
      /* Hack for chrome where the offset seems to be incorrect */
      if (clip_size - offset - image_size == 12)
        offset+=12;
    }
  offset+=BMP_HEADER_SIZE;
  p-=(ptrdiff_t)BMP_HEADER_SIZE;
  p[0]='B';
  p[1]='M';
  p[2]=(unsigned char) total_size;
  p[3]=(unsigned char) (total_size >> 8);
  p[4]=(unsigned char) (total_size >> 16);
  p[5]=(unsigned char) (total_size >> 24);
  p[10]=offset;
  read_info=CloneImageInfo(image_info);
  (void) CopyMagickString(read_info->magick,"BMP",MaxTextExtent);
  image=BlobToImage(read_info,clip_data,total_size,exception);
  read_info=DestroyImageInfo(read_info);
  clip_data=RelinquishMagickMemory(clip_data);
  return(image);
}
#endif /* MAGICKCORE_WINGDI32_DELEGATE */

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r C L I P B O A R D I m a g e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  RegisterCLIPBOARDImage() adds attributes for the clipboard "image format" to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterCLIPBOARDImage method is:
%
%      size_t RegisterCLIPBOARDImage(void)
%
*/
ModuleExport size_t RegisterCLIPBOARDImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("CLIPBOARD");
#if defined(MAGICKCORE_WINGDI32_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadCLIPBOARDImage;
  entry->encoder=(EncodeImageHandler *) WriteCLIPBOARDImage;
#endif
  entry->adjoin=MagickFalse;
  entry->format_type=ImplicitFormatType;
  entry->description=ConstantString("The system clipboard");
  entry->magick_module=ConstantString("CLIPBOARD");
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r C L I P B O A R D I m a g e                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  UnregisterCLIPBOARDImage() removes format registrations made by the
%  RGB module from the list of supported formats.
%
%  The format of the UnregisterCLIPBOARDImage method is:
%
%      UnregisterCLIPBOARDImage(void)
%
*/
ModuleExport void UnregisterCLIPBOARDImage(void)
{
  (void) UnregisterMagickInfo("CLIPBOARD");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e C L I P B O A R D I m a g e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WriteCLIPBOARDImage() writes an image to the system clipboard.
%
%  The format of the WriteCLIPBOARDImage method is:
%
%      MagickBooleanType WriteCLIPBOARDImage(const ImageInfo *image_info,
%        Image *image)
%
%  A description of each parameter follows.
%
%    o image_info: the image info.
%
%    o image:  The image.
%
*/
#if defined(MAGICKCORE_WINGDI32_DELEGATE)
static MagickBooleanType WriteCLIPBOARDImage(const ImageInfo *image_info,
  Image *image)
{
  ExceptionInfo
    *sans_exception;

  HANDLE
    clip_handle;

  ImageInfo
    *write_info;

  LPVOID
    clip_mem;

  size_t
    length;

  unsigned char
    *p;

  void
    *clip_data;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (IsEventLogging() != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (SetImageStorageClass(image,DirectClass) == MagickFalse)
    ThrowWriterException(CoderError,"UnableToWriteImageData");
  write_info=CloneImageInfo(image_info);
  if (image->matte == MagickFalse)
    (void) CopyMagickString(write_info->magick,"BMP3",MaxTextExtent);
  else
    (void) CopyMagickString(write_info->magick,"BMP",MaxTextExtent);
  sans_exception=AcquireExceptionInfo();
  clip_data=ImageToBlob(write_info,image,&length,sans_exception);
  sans_exception=DestroyExceptionInfo(sans_exception);
  write_info=DestroyImageInfo(write_info);
  if (clip_data == (void *) NULL)
    ThrowWriterException(CoderError,"UnableToWriteImageData");
  clip_handle=(HANDLE) GlobalAlloc(GMEM_MOVEABLE,length-BMP_HEADER_SIZE);
  if (clip_handle == (HANDLE) NULL)
    {
      clip_data=RelinquishMagickMemory(clip_data);
      ThrowWriterException(CoderError,"UnableToWriteImageData");
    }
  clip_mem=GlobalLock(clip_handle);
  if (clip_mem == (LPVOID) NULL)
    {
      (void) GlobalFree((HGLOBAL) clip_handle);
      clip_data=RelinquishMagickMemory(clip_data);
      ThrowWriterException(CoderError,"UnableToWriteImageData");
    }
  p=(unsigned char *) clip_data;
  p+=(ptrdiff_t) BMP_HEADER_SIZE;
  (void) memcpy(clip_mem,p,length-BMP_HEADER_SIZE);
  (void) GlobalUnlock(clip_mem);
  clip_data=RelinquishMagickMemory(clip_data);
  if (!OpenClipboard(NULL))
    {
      (void) GlobalFree((HGLOBAL) clip_handle);
      ThrowWriterException(CoderError,"UnableToWriteImageData");
    }
  (void) EmptyClipboard();
  if (image->matte == MagickFalse)
    SetClipboardData(CF_DIB,clip_handle);
  else
    SetClipboardData(CF_DIBV5,clip_handle);
  (void) CloseClipboard();
  CatchImageException(image);
  return(MagickTrue);
}
#endif /* MAGICKCORE_WINGDI32_DELEGATE */

