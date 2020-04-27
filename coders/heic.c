/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                        H   H  EEEEE  IIIII   CCCC                           %
%                        H   H  E        I    C                               %
%                        HHHHH  EEE      I    C                               %
%                        H   H  E        I    C                               %
%                        H   H  EEEEE  IIIII   CCCC                           %
%                                                                             %
%                                                                             %
%                        Read/Write Heic Image Format                         %
%                                                                             %
%                                 Dirk Farin                                  %
%                                 April 2018                                  %
%                                                                             %
%                         Copyright 2018 Struktur AG                          %
%                                                                             %
%                               Anton Kortunov                                %
%                               December 2017                                 %
%                                                                             %
%                      Copyright 2017-2018 YANDEX LLC.                        %
%                                                                             %
%  Copyright 1999-2020 ImageMagick Studio LLC, a non-profit organization      %
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
#include "magick/artifact.h"
#include "magick/blob.h"
#include "magick/blob-private.h"
#include "magick/client.h"
#include "magick/colorspace-private.h"
#include "magick/property.h"
#include "magick/display.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/image.h"
#include "magick/image-private.h"
#include "magick/list.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/monitor-private.h"
#include "magick/montage.h"
#include "magick/transform.h"
#include "magick/memory_.h"
#include "magick/memory-private.h"
#include "magick/option.h"
#include "magick/pixel-accessor.h"
#include "magick/quantum-private.h"
#include "magick/static.h"
#include "magick/string_.h"
#include "magick/string-private.h"
#include "magick/module.h"
#include "magick/utility.h"
#if defined(MAGICKCORE_HEIC_DELEGATE)
#if defined(MAGICKCORE_WINDOWS_SUPPORT)
#include <heif.h>
#else
#include <libheif/heif.h>
#endif
#endif

#if defined(MAGICKCORE_HEIC_DELEGATE)
#if !defined(MAGICKCORE_WINDOWS_SUPPORT)
static MagickBooleanType
  WriteHEICImage(const ImageInfo *,Image *,ExceptionInfo *);
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d H E I C I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadHEICImage retrieves an image via a file descriptor, decodes the image,
%  and returns it.  It allocates the memory necessary for the new Image
%  structure and returns a pointer to the new image.
%
%  The format of the ReadHEICImage method is:
%
%      Image *ReadHEICImage(const ImageInfo *image_info,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o exception: return any errors or warnings in this structure.
%
*/

static MagickBooleanType IsHeifSuccess(struct heif_error *error, Image *image)
{
  if (error->code == 0)
    return(MagickTrue);
  ThrowBinaryImageException(CorruptImageError,error->message,image->filename);
}

static Image *ReadHEICImage(const ImageInfo *image_info,
  ExceptionInfo *exception)
{
  const StringInfo
    *profile;

  heif_item_id
    exif_id;

  Image
    *image;

  int
    count,
    stride_y,
    stride_cb,
    stride_cr;

  MagickBooleanType
    preserve_orientation,
    status;

  size_t
    length;

  ssize_t
    y;

  struct heif_context
    *heif_context;

  struct heif_decoding_options
    *decode_options;

  struct heif_error
    error;

  struct heif_image
    *heif_image;

  struct heif_image_handle
    *image_handle;

  const uint8_t
    *p_y,
    *p_cb,
    *p_cr;

  void
    *file_data;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",
      image_info->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  image=AcquireImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFalse)
    return(DestroyImageList(image));
  if (GetBlobSize(image) > (MagickSizeType) SSIZE_MAX)
    ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
  length=(size_t) GetBlobSize(image);
  file_data=AcquireMagickMemory(length);
  if (file_data == (void *) NULL)
    ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
  if (ReadBlob(image,length,(unsigned char *) file_data) != (ssize_t) length)
    {
      file_data=RelinquishMagickMemory(file_data);
      ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
    }
  /*
    Decode HEIF file
  */
  heif_context=heif_context_alloc();
  error=heif_context_read_from_memory_without_copy(heif_context,file_data,
    length,NULL);
  if (IsHeifSuccess(&error,image) == MagickFalse)
    {
      heif_context_free(heif_context);
      file_data=RelinquishMagickMemory(file_data);
      return(DestroyImageList(image));
    }
  image_handle=(struct heif_image_handle *) NULL;
  error=heif_context_get_primary_image_handle(heif_context,&image_handle);
  if (IsHeifSuccess(&error,image) == MagickFalse)
    {
      heif_context_free(heif_context);
      file_data=RelinquishMagickMemory(file_data);
      return(DestroyImageList(image));
    }
#if LIBHEIF_NUMERIC_VERSION >= 0x01040000
  length=heif_image_handle_get_raw_color_profile_size(image_handle);
  if (length > 0)
    {
      unsigned char
        *color_buffer;

      /*
        Read color profile.
      */ 
      if ((MagickSizeType) length > GetBlobSize(image))
        {
          heif_image_handle_release(image_handle);
          heif_context_free(heif_context);
          file_data=RelinquishMagickMemory(file_data);
          ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
        }
      color_buffer=(unsigned char *) AcquireMagickMemory(length);
      if (color_buffer != (unsigned char *) NULL)
        {
          error=heif_image_handle_get_raw_color_profile(image_handle,
            color_buffer);
          if (error.code == 0)
            {
              StringInfo
                *profile;

              profile=BlobToStringInfo(color_buffer,length);
              if (profile != (StringInfo*) NULL)
                {
                  (void) SetImageProfile(image,"icc",profile);
                  profile=DestroyStringInfo(profile);
                }
            }
        }
      color_buffer=(unsigned char *) RelinquishMagickMemory(color_buffer);
    }
#endif
  count=heif_image_handle_get_list_of_metadata_block_IDs(image_handle,"Exif",
    &exif_id,1);
  if (count > 0)
    {
      size_t
        exif_size;

      unsigned char
        *exif_buffer;

      /*
        Read Exif profile.
      */
      exif_size=heif_image_handle_get_metadata_size(image_handle,exif_id);
      if ((MagickSizeType) exif_size > GetBlobSize(image))
        {
          heif_image_handle_release(image_handle);
          heif_context_free(heif_context);
          file_data=RelinquishMagickMemory(file_data);
          ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
        }
      exif_buffer=(unsigned char*) AcquireMagickMemory(exif_size);
      if (exif_buffer != (unsigned char*) NULL)
        {
          error=heif_image_handle_get_metadata(image_handle,
            exif_id,exif_buffer);
          if (error.code == 0)
            {
              StringInfo
                *profile;

              /*
                The first 4 byte should be skipped since they indicate the
                offset to the start of the TIFF header of the Exif data.
              */
              profile=(StringInfo*) NULL;
              if (exif_size > 8)
                profile=BlobToStringInfo(exif_buffer+4,(size_t) exif_size-4);
              if (profile != (StringInfo*) NULL)
                {
                  (void) SetImageProfile(image,"exif",profile);
                  profile=DestroyStringInfo(profile);
                }
            }
        }
      exif_buffer=(unsigned char *) RelinquishMagickMemory(exif_buffer);
  }
  /*
    Set image size.
  */
  image->depth=8;
  image->columns=(size_t) heif_image_handle_get_width(image_handle);
  image->rows=(size_t) heif_image_handle_get_height(image_handle);
  preserve_orientation=IsStringTrue(GetImageOption(image_info,
    "heic:preserve-orientation"));
  if (preserve_orientation == MagickFalse)
    (void) SetImageProperty(image,"exif:Orientation","1");
  if (image_info->ping != MagickFalse)
    {
      image->colorspace=YCbCrColorspace;
      heif_image_handle_release(image_handle);
      heif_context_free(heif_context);
      file_data=RelinquishMagickMemory(file_data);
      return(GetFirstImageInList(image));
    }
  status=SetImageExtent(image,image->columns,image->rows);
  if (status == MagickFalse)
    {
      heif_image_handle_release(image_handle);
      heif_context_free(heif_context);
      file_data=RelinquishMagickMemory(file_data);
      return(DestroyImageList(image));
    }
  /*
    Copy HEIF image into ImageMagick data structures
  */
  (void) SetImageColorspace(image,YCbCrColorspace);
  decode_options=(struct heif_decoding_options *) NULL;
  if (preserve_orientation == MagickTrue)
    {
      decode_options=heif_decoding_options_alloc();
      decode_options->ignore_transformations=1;
    }
  error=heif_decode_image(image_handle,&heif_image,heif_colorspace_YCbCr,
    heif_chroma_420,decode_options);
  if (decode_options != (struct heif_decoding_options *) NULL)
    heif_decoding_options_free(decode_options);
  if (IsHeifSuccess(&error,image) == MagickFalse)
    {
      heif_image_handle_release(image_handle);
      heif_context_free(heif_context);
      file_data=RelinquishMagickMemory(file_data);
      return(DestroyImageList(image));
    }
  /*
    Correct the width and height of the image.
  */
  image->columns=(size_t) heif_image_get_width(heif_image,heif_channel_Y);
  image->rows=(size_t) heif_image_get_height(heif_image,heif_channel_Y);
  status=SetImageExtent(image,image->columns,image->rows);
  if (status == MagickFalse)
    {
      heif_image_release(heif_image);
      heif_image_handle_release(image_handle);
      heif_context_free(heif_context);
      file_data=RelinquishMagickMemory(file_data);
      return(DestroyImageList(image));
    }
  p_y=heif_image_get_plane_readonly(heif_image,heif_channel_Y,&stride_y);
  p_cb=heif_image_get_plane_readonly(heif_image,heif_channel_Cb,&stride_cb);
  p_cr=heif_image_get_plane_readonly(heif_image,heif_channel_Cr,&stride_cr);
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    PixelPacket
      *q;

    register ssize_t
      x;

    q=QueueAuthenticPixels(image,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      break;
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      SetPixelRed(q,ScaleCharToQuantum((unsigned char) p_y[y*
        stride_y+x]));
      SetPixelGreen(q,ScaleCharToQuantum((unsigned char) p_cb[(y/2)*
        stride_cb+x/2]));
      SetPixelBlue(q,ScaleCharToQuantum((unsigned char) p_cr[(y/2)*
        stride_cr+x/2]));
      q++;
    }
    if (SyncAuthenticPixels(image,exception) == MagickFalse)
      break;
  }
  heif_image_release(heif_image);
  heif_image_handle_release(image_handle);
  heif_context_free(heif_context);
  file_data=RelinquishMagickMemory(file_data);
  profile=GetImageProfile(image,"icc");
  if (profile != (const StringInfo *) NULL)
    (void) TransformImageColorspace(image,sRGBColorspace);
  return(GetFirstImageInList(image));
}
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s H E I C                                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  IsHEIC() returns MagickTrue if the image format type, identified by the
%  magick string, is Heic.
%
%  The format of the IsHEIC method is:
%
%      MagickBooleanType IsHEIC(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o magick: compare image format pattern against these bytes.
%
%    o length: Specifies the length of the magick string.
%
*/
static MagickBooleanType IsHEIC(const unsigned char *magick,const size_t length)
{
  if (length < 12)
    return(MagickFalse);
  if (LocaleNCompare((const char *) magick+8,"heic",4) == 0)
    return(MagickTrue);
  return(MagickFalse);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r H E I C I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  RegisterHEICImage() adds attributes for the HEIC image format to the list of
%  supported formats.  The attributes include the image format tag, a method
%  to read and/or write the format, whether the format supports the saving of
%  more than one frame to the same file or blob, whether the format supports
%  native in-memory I/O, and a brief description of the format.
%
%  The format of the RegisterHEICImage method is:
%
%      size_t RegisterHEICImage(void)
%
*/
ModuleExport size_t RegisterHEICImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("HEIC");
#if defined(MAGICKCORE_HEIC_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadHEICImage;
#if !defined(MAGICKCORE_WINDOWS_SUPPORT)
  entry->encoder=(EncodeImageHandler *) WriteHEICImage;
#endif
#endif
  entry->magick=(IsImageFormatHandler *) IsHEIC;
  entry->description=ConstantString("Apple High efficiency Image Format");
  entry->mime_type=ConstantString("image/x-heic");
#if defined(LIBHEIF_VERSION)
  entry->version=ConstantString(LIBHEIF_VERSION);
#endif
  entry->magick_module=ConstantString("HEIC");
  entry->adjoin=MagickFalse;
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r H E I C I m a g e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  UnregisterHEICImage() removes format registrations made by the HEIC module
%  from the list of supported formats.
%
%  The format of the UnregisterHEICImage method is:
%
%      UnregisterHEICImage(void)
%
*/
ModuleExport void UnregisterHEICImage(void)
{
  (void) UnregisterMagickInfo("HEIC");
}


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e H E I C I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  WriteHEICImage() writes an HEIF image using the libheif library.
%
%  The format of the WriteHEICImage method is:
%
%      MagickBooleanType WriteHEICImage(const ImageInfo *image_info,
%        Image *image)
%
%  A description of each parameter follows.
%
%    o image_info: the image info.
%
%    o image:  The image.
%
%    o exception:  return any errors or warnings in this structure.
%
*/
#if defined(MAGICKCORE_HEIC_DELEGATE) && !defined(MAGICKCORE_WINDOWS_SUPPORT)
static struct heif_error heif_write_func(struct heif_context *context,
  const void* data,size_t size,void* userdata)
{
  Image
    *image;

  struct heif_error
    error_ok;

  (void) context;
  image=(Image*) userdata;
  (void) WriteBlob(image,size,(const unsigned char *) data);
  error_ok.code=heif_error_Ok;
  error_ok.subcode=heif_suberror_Unspecified;
  error_ok.message="ok";
  return(error_ok);
}

static MagickBooleanType WriteHEICImage(const ImageInfo *image_info,
  Image *image,ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  MagickOffsetType
    scene;

  ssize_t
    y;

  struct heif_context
    *heif_context;

  struct heif_encoder
    *heif_encoder;

  struct heif_image
    *heif_image;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,exception);
  if (status == MagickFalse)
    return(status);
  scene=0;
  heif_context=heif_context_alloc();
  heif_image=(struct heif_image*) NULL;
  heif_encoder=(struct heif_encoder*) NULL;
  do
  {
    const PixelPacket
      *p;

#if LIBHEIF_NUMERIC_VERSION >= 0x01040000
    const StringInfo
      *profile;
#endif

    int
      stride_y,
      stride_cb,
      stride_cr;

    struct heif_error
      error;

    struct heif_writer
      writer;

    uint8_t
      *p_y,
      *p_cb,
      *p_cr;

    /*
      Transform colorspace to YCbCr.
    */
    if (image->colorspace != YCbCrColorspace)
      status=TransformImageColorspace(image,YCbCrColorspace);
    if (status == MagickFalse)
      break;
    /*
      Initialize HEIF encoder context.
    */
    error=heif_image_create((int) image->columns,(int) image->rows,
      heif_colorspace_YCbCr,heif_chroma_420,&heif_image);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
#if LIBHEIF_NUMERIC_VERSION >= 0x01040000
    profile=GetImageProfile(image,"icc");
    if (profile != (StringInfo *) NULL)
      (void) heif_image_set_raw_color_profile(heif_image,"prof",
        GetStringInfoDatum(profile),GetStringInfoLength(profile));
#endif
    error=heif_image_add_plane(heif_image,heif_channel_Y,(int) image->columns,
      (int) image->rows,8);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
    error=heif_image_add_plane(heif_image,heif_channel_Cb,
      ((int) image->columns+1)/2,((int) image->rows+1)/2,8);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
    error=heif_image_add_plane(heif_image,heif_channel_Cr,
      ((int) image->columns+1)/2,((int) image->rows+1)/2,8);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
    p_y=heif_image_get_plane(heif_image,heif_channel_Y,&stride_y);
    p_cb=heif_image_get_plane(heif_image,heif_channel_Cb,&stride_cb);
    p_cr=heif_image_get_plane(heif_image,heif_channel_Cr,&stride_cr);
    /*
      Copy image to heif_image
    */
    for (y=0; y < (ssize_t) image->rows; y++)
    {
      register ssize_t
        x;

      p=GetVirtualPixels(image,0,y,image->columns,1,exception);
      if (p == (const PixelPacket *) NULL)
        {
          status=MagickFalse;
          break;
        }
      if ((y & 0x01) == 0)
        for (x=0; x < (ssize_t) image->columns; x+=2)
        {
          p_y[y*stride_y+x]=ScaleQuantumToChar(GetPixelRed(p));
          p_cb[y/2*stride_cb+x/2]=ScaleQuantumToChar(GetPixelGreen(p));
          p_cr[y/2*stride_cr+x/2]=ScaleQuantumToChar(GetPixelBlue(p));
          p++;
          if ((x+1) < (ssize_t) image->columns)
            {
              p_y[y*stride_y+x+1]=ScaleQuantumToChar(GetPixelRed(p));
              p++;
            }
        }
      else
        for (x=0; x < (ssize_t) image->columns; x++)
        {
          p_y[y*stride_y+x]=ScaleQuantumToChar(GetPixelRed(p));
          p++;
        }
      if (image->previous == (Image *) NULL)
        {
          status=SetImageProgress(image,SaveImageTag,(MagickOffsetType) y,
            image->rows);
          if (status == MagickFalse)
            break;
        }
    }
    if (status == MagickFalse)
      break;
    /*
      Code and actually write the HEIC image
    */
    error=heif_context_get_encoder_for_format(heif_context,
      heif_compression_HEVC,&heif_encoder);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
    if (image_info->quality != UndefinedCompressionQuality)
      {
        error=heif_encoder_set_lossy_quality(heif_encoder,
          (int) image_info->quality);
        status=IsHeifSuccess(&error,image);
        if (status == MagickFalse)
          break;
      }
    error=heif_context_encode_image(heif_context,heif_image,heif_encoder,
      (const struct heif_encoding_options*) NULL,
      (struct heif_image_handle**) NULL);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
    writer.writer_api_version=1;
    writer.write=heif_write_func;
    error=heif_context_write(heif_context,&writer,image);
    status=IsHeifSuccess(&error,image);
    if (status == MagickFalse)
      break;
    if (GetNextImageInList(image) == (Image *) NULL)
      break;
    image=SyncNextImageInList(image);
    status=SetImageProgress(image,SaveImagesTag,scene,
      GetImageListLength(image));
    if (status == MagickFalse)
      break;
    heif_encoder_release(heif_encoder);
    heif_encoder=(struct heif_encoder*) NULL;
    heif_image_release(heif_image);
    heif_image=(struct heif_image*) NULL;
    scene++;
  } while (image_info->adjoin != MagickFalse);
  if (heif_encoder != (struct heif_encoder*) NULL)
    heif_encoder_release(heif_encoder);
  if (heif_image != (struct heif_image*) NULL)
    heif_image_release(heif_image);
  heif_context_free(heif_context);
  (void) CloseBlob(image);
  return(status);
}
#endif
