# ImageMagick (legacy)

[![Build Status](https://github.com/ImageMagick/ImageMagick/workflows/main/badge.svg)](https://github.com/ImageMagick/ImageMagick/actions)
[![Fuzzing Status](https://oss-fuzz-build-logs.storage.googleapis.com/badges/imagemagick.svg)](https://bugs.chromium.org/p/oss-fuzz/issues/list?sort=-opened&can=1&q=proj:imagemagick)
[![Donate](https://img.shields.io/badge/%24-donate-ff00ff.svg)](https://github.com/sponsors/ImageMagick)

<p align="center">
<img align="center" src="https://imagemagick.org/image/wizard.png" alt="ImageMagick logo" width="265" height="353"/>
</p>

Legacy [ImageMagick®](https://legacy.imagemagick.org/) is a free and [open-source](https://legacy.imagemagick.org/script/license.php) software suite for displaying, converting, and editing raster image and vector image files. It can read and write over 200 image file [formats](https://legacy.imagemagick.org/script/formats.php), and can support a wide range of image manipulation operations, such as resizing, cropping, and color correction.

#### What is ImageMagick?

ImageMagick is written in C and is available for a wide range of operating systems, including Linux, macOS, and Windows. It can be used as a standalone application, or as a library that can be integrated into other software programs.

The main website for legacy ImageMagick can be found at [https://legacy.imagemagick.org](https://legacy.imagemagick.org/). The source code for this software can be accessed through the repository located at [https://github.com/ImageMagick/ImageMagick6](https://github.com/ImageMagick/ImageMagick6). In addition, a more recent version of ImageMagick, version 7, can be found at [https://imagemagick.org](https://imagemagick.org/).

#### Features and Capabilities

One of the key features of ImageMagick is its support for scripting and automation. This allows users to create complex image manipulation pipelines that can be run automatically, without the need for manual intervention. This can be especially useful for tasks that require the processing of large numbers of images, or for tasks that need to be performed on a regular basis.

In addition to its core image manipulation capabilities, ImageMagick also includes a number of other features, such as support for animation, color management, and image rendering. These features make it a versatile tool for a wide range of image-related tasks, including graphic design, scientific visualization, and digital art.

Overall, ImageMagick is a powerful and versatile software suite for displaying, converting, and editing image files. Its support for scripting and automation, along with its other features, make it a valuable tool for a wide range of image-related tasks.

Here are just a few [examples](https://legacy.imagemagick.org/script/examples.php) of what ImageMagick can do:

* [Animation](https://legacy.imagemagick.org/script/command-line-options.php#bilateral-blur): non-linear, edge-preserving, and noise-reducing smoothing filter.
* [Bilateral Blur](https://legacy.imagemagick.org/script/command-line-options.php#bilateral-blur): non-linear, edge-preserving, and noise-reducing smoothing filter.
* [Color management](https://legacy.imagemagick.org/script/color-management.php): accurate color management with color profiles or in lieu of-- built-in gamma compression or expansion as demanded by the colorspace.
* [Color thresholding](https://legacy.imagemagick.org/script/color-management.php) force all pixels in the color range to white otherwise black.
* [Command-line processing](https://legacy.imagemagick.org/script/command-line-processing.php) utilize ImageMagick from the command-line.
* [Complex text layout](https://en.wikipedia.org/wiki/Complex_text_layout) bidirectional text support and shaping.
* [Composite](https://legacy.imagemagick.org/script/composite.php): overlap one image over another.
* [Connected component labeling](https://legacy.imagemagick.org/script/connected-components.php): uniquely label connected regions in an image.
* [Convex hull](https://legacy.imagemagick.org/script/convex-hull.php) smallest area convex polygon containing the image foreground objects. In addition, the minimum bounding box and unrotate angle are also generated.
* [Decorate](https://legacy.imagemagick.org/Usage/crop/): add a border or frame to an image.
* [Delineate image features](https://legacy.imagemagick.org/Usage/transform/#vision): Canny edge detection, mean-shift, Hough lines.
* [Discrete Fourier transform](https://legacy.imagemagick.org/Usage/fourier/): implements the forward and inverse [DFT](http://en.wikipedia.org/wiki/Discrete_Fourier_transform).
* [Distributed pixel cache](https://legacy.imagemagick.org/script/distribute-pixel-cache.php): offload intermediate pixel storage to one or more remote servers.
* [Draw](https://legacy.imagemagick.org/Usage/draw/): add shapes or text to an image.
* [Encipher or decipher an image](https://legacy.imagemagick.org/script/cipher.php): convert ordinary images into unintelligible gibberish and back again.
* [Format conversion](https://legacy.imagemagick.org/script/convert.php): convert an image from one [format](https://imagemagick.org/script/formats.php) to another (e.g.  PNG to JPEG).
* [Generalized pixel distortion](https://legacy.imagemagick.org/Usage/distorts/): correct for, or induce image distortions including perspective.
* [Heterogeneous distributed processing](https://legacy.imagemagick.org/script/architecture.php#distributed): certain algorithms are OpenCL-enabled to take advantage of speed-ups offered by executing in concert across heterogeneous platforms consisting of CPUs, GPUs, and other processors.
* [High dynamic-range images](https://legacy.imagemagick.org/script/high-dynamic-range.php): accurately represent the wide range of intensity levels found in real scenes ranging from the brightest direct sunlight to the deepest darkest shadows.
* [Histogram equalization](https://legacy.imagemagick.org/script/clahe.php) use adaptive histogram equalization to improve contrast in images.
* [Image cache](https://legacy.imagemagick.org/script/magick-cache.php): secure methods and tools to cache images, image sequences, video, audio or metadata in a local folder.
* [Image calculator](https://legacy.imagemagick.org/script/fx.php): apply a mathematical expression to an image or image channels.
* [Image gradients](https://legacy.imagemagick.org/script/gradient.php): create a gradual blend of one color whose shape is horizontal, vertical, circular, or elliptical.
* [Image identification](https://legacy.imagemagick.org/script/identify.php): describe the format and attributes of an image.
* [ImageMagick on the iPhone](https://legacy.imagemagick.org/script/download.php#iOS): convert, edit, or compose images on your iPhone.
* [Large image support](https://legacy.imagemagick.org/script/architecture.php#tera-pixel): read, process, or write mega-, giga-, or tera-pixel image sizes.
* [Montage](https://legacy.imagemagick.org/script/montage.php): juxtapose image thumbnails on an image canvas.
* [Morphology of shapes](https://legacy.imagemagick.org/Usage/morphology/): extract features, describe shapes and recognize patterns in images.
* [Motion picture support](https://legacy.imagemagick.org/script/motion-picture.php): read and write the common image formats used in digital film work.
* [Multispectral imagery](https://legacy.imagemagick.org/script/architecture.php#multispectral): support multispectral imagery up to 64 bands.
* [Noise and color reduction](https://legacy.imagemagick.org/Usage/transform/#vision) Kuwahara Filter, mean-shift.
* [Perceptual hash](http://www.fmwconcepts.com/misc_tests/perceptual_hash_test_results_510/index.html): maps visually identical images to the same or similar hash-- useful in image retrieval, authentication, indexing, or copy detection as well as digital watermarking.
* [Special effects](https://legacy.imagemagick.org/Usage/blur/): blur, sharpen, threshold, or tint an image.
* [Text & comments](https://legacy.imagemagick.org/Usage/text/): insert descriptive or artistic text in an image.
* [Threads of execution support](https://legacy.imagemagick.org/script/architecture.php#threads): ImageMagick is thread safe and most internal algorithms are OpenMP-enabled to take advantage of speed-ups offered by multicore processor chips.
* [Transform](https://legacy.imagemagick.org/Usage/resize/): resize, rotate, deskew, crop, flip or trim an image.
* [Transparency](https://legacy.imagemagick.org/Usage/masking/): render portions of an image invisible.
* [Virtual pixel support](https://legacy.imagemagick.org/script/architecture.php#virtual-pixels): convenient access to pixels outside the image region.

[Examples of ImageMagick Usage](https://legacy.imagemagick.org/Usage/), demonstrates how to use the software from the [command line](https://legacy.imagemagick.org/script/command-line-processing.php) to achieve various effects. There are also several scripts available on the website called [Fred's ImageMagick Scripts](http://www.fmwconcepts.com/imagemagick/), which can be used to apply geometric transforms, blur and sharpen images, remove noise, and perform other operations. Additionally, there is a tool called [Magick.NET](https://github.com/dlemstra/Magick.NET) that allows users to access the functionality of ImageMagick without having to install the software on their own systems. Finally, the website also includes a [Cookbook](http://im.snibgo.com/) with tips and examples for using ImageMagick on Windows systems.

#### News

ImageMagick best practices **strongly** encourages you to configure a [security policy](https://legacy.imagemagick.org/script/security-policy.php) that suits your local environment.

Now that ImageMagick [version 7](https://imagemagick.org) is released, we recommend upgrading from version 6. Learn how ImageMagick version 7 differs from previous versions with our [porting guide](https://imagemagick.org/script/porting.php).

Want more performance from ImageMagick? Try these options:

* add more memory to your system, see the [pixel cache](https://legacy.imagemagick.org/script/architecture.php#cache);
* add more cores to your system, see [threads of execution support](https://legacy.imagemagick.org/script/architecture.php#threads);
* reduce lock contention with the [tcmalloc](http://goog-perftools.sourceforge.net/doc/tcmalloc.html) memory allocation library;
* push large images to a solid-state drive, see [large image support](https://legacy.imagemagick.org/script/architecture.php#tera-pixel).

If these options are prohibitive, you can reduce the quality of the image results. The default build is Q16 HDRI. If you disable [HDRI](https://legacy.imagemagick.org/script/high-dynamic-range.php), you use half the memory and instead of predominantly floating point operations, you use the typically more efficient integer operations. The tradeoff is reduced precision and you cannot process out of range pixel values (e.g. negative). If you build the Q8 non-HDRI version of ImageMagick, you again reduce the memory requirements in half-- and once again there is a tradeoff, even less precision and no out of range pixel values. For a Q8 non-HDRI build of ImageMagick, use these configure script options: --with-quantum-depth=8 --disable-hdri.
