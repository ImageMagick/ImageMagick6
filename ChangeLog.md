# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [6.9.12-43](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-42...6.9.12-43) - 2022-03-20

### Commits

- magick: support getentropy() [`d29a057`](https://github.com/ImageMagick/ImageMagick6/commit/d29a057a3689f7b944b879dee92e7d39a33bf3cc)
- Coders: eliminate compiler warnings [`ee332c5`](https://github.com/ImageMagick/ImageMagick6/commit/ee332c511445a1fb2934f40246c3c958aefd73e9)
- ... [`96d197f`](https://github.com/ImageMagick/ImageMagick6/commit/96d197f14932d4ba8a116e06fe306403ea1e32f1)
- Pull request: https://github.com/ImageMagick/ImageMagick/pull/4963 [`450949e`](https://github.com/ImageMagick/ImageMagick6/commit/450949ed017f009b399c937cf362f0058eacc5fa)
- Coders: https://github.com/ImageMagick/ImageMagick/issues/4947 [`78f03b6`](https://github.com/ImageMagick/ImageMagick6/commit/78f03b619d08d7c2e0fcaccab407e3ac93c2ee8f)
- Coders: PS and EPS %%BoundingBox not being parsed #4961 [`2a67214`](https://github.com/ImageMagick/ImageMagick6/commit/2a67214abc2410931064b1f4e2c01f177d768edf)
- Changed the format of MAGICK_GIT_REVISION and use this in -version. [`bd49573`](https://github.com/ImageMagick/ImageMagick6/commit/bd495730646575af3c867ed09adc8588061079ab)
- https://github.com/ImageMagick/ImageMagick/issues/4927 [`932cf02`](https://github.com/ImageMagick/ImageMagick6/commit/932cf023db383394c4ec304c95730aed631c57d2)
- Coders: proper check for out of bounds per https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=45640 [`5468786`](https://github.com/ImageMagick/ImageMagick6/commit/5468786406b323fef6a5fe50bc56dabde3da4130)
- https://github.com/ImageMagick/ImageMagick/issues/4927 [`594366f`](https://github.com/ImageMagick/ImageMagick6/commit/594366fd3a5268d0456c4f60c5746a9f586ab035)
- correct date format [`625ff11`](https://github.com/ImageMagick/ImageMagick6/commit/625ff113cc9acf864c56c266471829bb19439299)
- getentropy() requires sys/random.h include [`005bac2`](https://github.com/ImageMagick/ImageMagick6/commit/005bac2904c18bc6f03a2ac31bdda51005411355)
- no need to check for &lt; 0 [`dead6a8`](https://github.com/ImageMagick/ImageMagick6/commit/dead6a806786eb2712dd76c38e3ff75c2f94997b)
- build: pending release [`775c781`](https://github.com/ImageMagick/ImageMagick6/commit/775c7817f3700514173e0655776e0d9465e93d6c)
- build: release [`2d5e8e3`](https://github.com/ImageMagick/ImageMagick6/commit/2d5e8e387e1c6daaf45f8efd1c24ee6a53e70e01)
- Coders: https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=42549 [`de6ada9`](https://github.com/ImageMagick/ImageMagick6/commit/de6ada9a068b01494bfb848024ed46942da9d238)

## [6.9.12-42](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-41...6.9.12-42) - 2022-03-04

### Commits

- auto-generate the change log from git commit [`553ca1b`](https://github.com/ImageMagick/ImageMagick6/commit/553ca1b6e5bcc7d89af226cecfa6b6197a90a98c)
- https://github.com/ImageMagick/ImageMagick/issues/4876 [`52e5cc1`](https://github.com/ImageMagick/ImageMagick6/commit/52e5cc1988b15b9a6f3d7e9e3b7b72e3a346cfc9)
- https://github.com/ImageMagick/ImageMagick/issues/966 [`d9544e7`](https://github.com/ImageMagick/ImageMagick6/commit/d9544e78bfe55361b7768ddb00eb24b7f33f2137)
- pending release [`4f420a4`](https://github.com/ImageMagick/ImageMagick6/commit/4f420a43ce112948baa8de9a1ba56ee7b17afb0f)
- ... [`8f1f6c3`](https://github.com/ImageMagick/ImageMagick6/commit/8f1f6c32bfb13ac1e8b8a7ce2f59a28ef06cb18b)
- https://github.com/ImageMagick/ImageMagick/issues/4870 [`8b7b17c`](https://github.com/ImageMagick/ImageMagick6/commit/8b7b17c8fef72dab479e6ca676676d8c5e395dd6)
- escape \n character [`32a4bf3`](https://github.com/ImageMagick/ImageMagick6/commit/32a4bf395e8201896c0a21f95661766bed41e470)
- https://github.com/ImageMagick/ImageMagick/issues/966 [`2db42a9`](https://github.com/ImageMagick/ImageMagick6/commit/2db42a9e1dde7e88dc370deb04a3be48c01dedf5)
- throw exception on reserved filename character (\xff) [`8215fc2`](https://github.com/ImageMagick/ImageMagick6/commit/8215fc2e71513877d3040fbddfd1f16ca54499a7)
- https://github.com/ImageMagick/ImageMagick/issues/4888 [`2eb8b86`](https://github.com/ImageMagick/ImageMagick6/commit/2eb8b8660dac0d647a7045a6af7f3e8fcca1d8f8)
- https://github.com/ImageMagick/ImageMagick/issues/4888 [`ba2242d`](https://github.com/ImageMagick/ImageMagick6/commit/ba2242da46bfbd2cc4890486ff147a0113e08735)
- ... [`4c2da37`](https://github.com/ImageMagick/ImageMagick6/commit/4c2da37f2bcc98059f44cecf304e8b3c53664bfd)
- https://github.com/ImageMagick/ImageMagick/issues/966 [`bb79523`](https://github.com/ImageMagick/ImageMagick6/commit/bb795235696e2ace0f3d0b5703065a4b9a882f04)
- pending release [`dad876f`](https://github.com/ImageMagick/ImageMagick6/commit/dad876ff6b5e873bc59e0661d40e157eb599fcc1)
- ChangeLog =&gt; ChangeLog.md [`8a6726a`](https://github.com/ImageMagick/ImageMagick6/commit/8a6726af81ac40b41e962cafa8fd014d2659d432)
- Changed trigger for release. [`552bddd`](https://github.com/ImageMagick/ImageMagick6/commit/552bddd79749d8195cf5a1871929076adf9a479e)
- canonical copyright notice [`1e5a283`](https://github.com/ImageMagick/ImageMagick6/commit/1e5a28310d73e9c8c29fad113c872351340595a3)
- Fixed memory leak in ThumbnailImage. [`161f49b`](https://github.com/ImageMagick/ImageMagick6/commit/161f49b3b6a7d3121a566654f12916700d7f2d07)

## [6.9.12-41](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-40...6.9.12-41) - 2022-02-21

### Commits

- ... [`757c88c`](https://github.com/ImageMagick/ImageMagick6/commit/757c88cfe941df0cff8f2fef4681bd2b665c091c)
- Removed the xtrn coder. [`768f648`](https://github.com/ImageMagick/ImageMagick6/commit/768f648cce36a641b54092d78117435996c74a9a)
- rename method to TLS-moniker, thread local storage [`8860c28`](https://github.com/ImageMagick/ImageMagick6/commit/8860c28c64ae2cf5717e309325592c1ccb7cb969)
- Removed NTGhostscriptDLL and NTGhostscriptLoadDLL from the private header. [`70b7dfa`](https://github.com/ImageMagick/ImageMagick6/commit/70b7dfaf4d2f75af8b649d542d49374d6f447c11)
- remove reference to ImageMagickObject [`d64a152`](https://github.com/ImageMagick/ImageMagick6/commit/d64a15289a17a9d1d9856758f2ba82b75325f370)
- Fixes for installation in a folder that contains non ASCII characters. [`e3d32a2`](https://github.com/ImageMagick/ImageMagick6/commit/e3d32a2bdb9e50ddb2fd5966c847f0726e128815)
- ... [`695af8d`](https://github.com/ImageMagick/ImageMagick6/commit/695af8d4be0d25b36129d7b3fdf5a1b991216784)
- https://github.com/ImageMagick/ImageMagick/issues/4843 [`b24793c`](https://github.com/ImageMagick/ImageMagick6/commit/b24793c396083176cbf019a09847ad3ab427e240)
- https://github.com/ImageMagick/ImageMagick/issues/4761 [`77d68d3`](https://github.com/ImageMagick/ImageMagick6/commit/77d68d3e554ecd0e38ceb6a3f1decf65a69362c5)
- don't over-allocate thread-specific data [`b61069a`](https://github.com/ImageMagick/ImageMagick6/commit/b61069a33bab43a022992b3f7c81a50e06a7b45a)
- ... [`45d3733`](https://github.com/ImageMagick/ImageMagick6/commit/45d37331ef1a38712740e9bd7090fb855557b7cb)
- cosmetic [`6831beb`](https://github.com/ImageMagick/ImageMagick6/commit/6831bebd3067bddc10e954fe09bc98a3e6947be7)
- Removed the xtrn coder. [`854e7be`](https://github.com/ImageMagick/ImageMagick6/commit/854e7be5f0ce94c0a431d49a1c82a9eb50916be4)
- fix compiler exception under Cygwin [`32315c9`](https://github.com/ImageMagick/ImageMagick6/commit/32315c92a4e31c0b75fb88548c0bf40242f0e5f1)
- https://github.com/ImageMagick/ImageMagick/issues/4867 [`8c1bf89`](https://github.com/ImageMagick/ImageMagick6/commit/8c1bf8917a7a23daa6aaa03bb4293fd9ff7859a2)
- remove references to ImageMagickObject [`1e63c5c`](https://github.com/ImageMagick/ImageMagick6/commit/1e63c5c2d7f2c1d5c6aba0e8935ee855656cbb46)
- ... [`ba6e51f`](https://github.com/ImageMagick/ImageMagick6/commit/ba6e51f8e3b49c3d5015df5c4d152e07a37007aa)
- pending release [`9b99699`](https://github.com/ImageMagick/ImageMagick6/commit/9b9969944c92ccaf4fa7d34c1c258a794a1e23b9)
- pending release [`9ce4eba`](https://github.com/ImageMagick/ImageMagick6/commit/9ce4ebad1337a10bc9d6b74bddd57ad7dc3cde70)
- cosmetic [`c02d827`](https://github.com/ImageMagick/ImageMagick6/commit/c02d827078d59950e19e169ffeb3d988d0e1185c)
- pending release [`8a8673a`](https://github.com/ImageMagick/ImageMagick6/commit/8a8673a9bc1a7b915252645f305a65f0c990b491)
- https://github.com/ImageMagick/ImageMagick/issues/4865 [`e6d7f78`](https://github.com/ImageMagick/ImageMagick6/commit/e6d7f782fc1b6484c52fe7fb987c06559b489726)
- pending release [`e7418d5`](https://github.com/ImageMagick/ImageMagick6/commit/e7418d54c54b4646505ba95ce6458f352a94debf)
- pending release [`b855d8e`](https://github.com/ImageMagick/ImageMagick6/commit/b855d8ec0bb360deb7d80a14b5c1a5a1ffc47ee1)
- no need for conditional compile [`d5fe059`](https://github.com/ImageMagick/ImageMagick6/commit/d5fe0590573b15208f302d57e0b1c97a60e3d16d)
- off-by-one fix [`d0a2bc4`](https://github.com/ImageMagick/ImageMagick6/commit/d0a2bc44117217a7619d6ade90af0f40d9321c6e)
- Whitespace. [`b36de79`](https://github.com/ImageMagick/ImageMagick6/commit/b36de79c6cb913f4423f7eb71901d9f07946f573)
- Raise exception when image could not be read but no exception was raised. [`3e15c68`](https://github.com/ImageMagick/ImageMagick6/commit/3e15c68efcb1e6383c93e7dfe38ba6c37e614d1b)
- pending release [`fd143dc`](https://github.com/ImageMagick/ImageMagick6/commit/fd143dc849b6c191464f40e581b0abe344b6e41e)
- ... [`cecdf6f`](https://github.com/ImageMagick/ImageMagick6/commit/cecdf6f89642589221edc543144d45c5bde71b77)
- https://github.com/ImageMagick/ImageMagick/discussions/4755 [`1e86532`](https://github.com/ImageMagick/ImageMagick6/commit/1e8653229aeea1a6731ca3632bf5963b417312ed)

## [6.9.12-40](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-39...6.9.12-40) - 2022-02-15

### Commits

- cosmetic [`1da04da`](https://github.com/ImageMagick/ImageMagick6/commit/1da04dabe110e22954b33927567544b33e97b7a7)
- https://github.com/ImageMagick/ImageMagick/issues/4841 [`f5aeb09`](https://github.com/ImageMagick/ImageMagick6/commit/f5aeb0989d9889d85b2d66a106a670386872a8c6)
- ... [`4fd78b8`](https://github.com/ImageMagick/ImageMagick6/commit/4fd78b838c09c88ff3acf43a0799a002d2f873cf)
- fix unitialized value [`ce4d5cb`](https://github.com/ImageMagick/ImageMagick6/commit/ce4d5cb663cb3d701d63515edbeee561b71eae39)
- off-by-one fix [`409d6db`](https://github.com/ImageMagick/ImageMagick6/commit/409d6db86bae76c8f7401dc1c09c4349b8ca8352)
- display last debugging character [`e6a76f8`](https://github.com/ImageMagick/ImageMagick6/commit/e6a76f8bfb9a8edfbd4cdc44e79eb080f164cf71)
- https://github.com/ImageMagick/ImageMagick/issues/4837 [`a339e1f`](https://github.com/ImageMagick/ImageMagick6/commit/a339e1f47dd09d1765e971f7e104d34a2e50785c)
- pending release [`3264d72`](https://github.com/ImageMagick/ImageMagick6/commit/3264d72944d6f2df8f80ecb3d837da1431db37a6)
- off-by-one fix [`e41e298`](https://github.com/ImageMagick/ImageMagick6/commit/e41e29898936ca76b0def5126771733e0954191e)
- https://github.com/ImageMagick/ImageMagick/issues/4837 [`00e5d3a`](https://github.com/ImageMagick/ImageMagick6/commit/00e5d3a9a033182fcf704e4b1eae9e569fb85244)
- https://github.com/ImageMagick/ImageMagick/issues/4822 [`5a76293`](https://github.com/ImageMagick/ImageMagick6/commit/5a7629343bb280a1a177818e6e40776c7484d649)
- one off when debugging [`cb6374d`](https://github.com/ImageMagick/ImageMagick6/commit/cb6374d6fe7fec6651b1d1dd4ee7ec97c662c610)
- revert [`dc25885`](https://github.com/ImageMagick/ImageMagick6/commit/dc25885dfb4d516d6ef58ba77bfc47e8799acfed)
- alpha is never zero [`ff04a51`](https://github.com/ImageMagick/ImageMagick6/commit/ff04a51f4f89813c319f157c0aa993f36b944815)

## [6.9.12-39](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-38...6.9.12-39) - 2022-02-12

### Commits

- possible performance optimization [`1e04814`](https://github.com/ImageMagick/ImageMagick6/commit/1e04814e2e28c9a22f082b5c87cc5cf20642ad0d)
- https://github.com/ImageMagick/ImageMagick/discussions/4813 [`666ab9a`](https://github.com/ImageMagick/ImageMagick6/commit/666ab9ad9552fac12f92d2cf53173bea3d848255)
- ... [`e5ab86b`](https://github.com/ImageMagick/ImageMagick6/commit/e5ab86b9f52a8452fb00099f29a51763a5b114ff)
- https://github.com/ImageMagick/ImageMagick/issues/4830 [`409d422`](https://github.com/ImageMagick/ImageMagick6/commit/409d42205927c98cbb852ca96e109716f38f04ab)
- correct copyright year [`99ef124`](https://github.com/ImageMagick/ImageMagick6/commit/99ef124d080560a9df5a0c177a82c3ccc2ca6ca9)
- optimize reading of XPM properties [`cd103b8`](https://github.com/ImageMagick/ImageMagick6/commit/cd103b81ca7814533192f340053b388c6825ec83)
- ... [`bcf9658`](https://github.com/ImageMagick/ImageMagick6/commit/bcf9658a637a7c6993c7203382235fd3fabb7015)
- cosmetic [`5683607`](https://github.com/ImageMagick/ImageMagick6/commit/56836073a8cc42127b265280dfb0d5dcb4bc915b)
- Removed IsAVI check. [`6eb9f96`](https://github.com/ImageMagick/ImageMagick6/commit/6eb9f96e781996b71ead9d25182be0e84bfdb89f)
- Corrected UTF-16 big endian encoding. [`71e590e`](https://github.com/ImageMagick/ImageMagick6/commit/71e590ed3885ef5e2d48918809d8a3a8cfefccba)
- pending release [`002c3d7`](https://github.com/ImageMagick/ImageMagick6/commit/002c3d7c493de002eaa605ade574830e7e8d1693)
- prevent integer overflow [`a69648d`](https://github.com/ImageMagick/ImageMagick6/commit/a69648d9d3eb9855eeb6089a692c689581d85cff)
- https://github.com/ImageMagick/ImageMagick/issues/4822 [`0977428`](https://github.com/ImageMagick/ImageMagick6/commit/097742836e252be7aba65c00877722f5eae8e851)
- ... [`fb8b7d6`](https://github.com/ImageMagick/ImageMagick6/commit/fb8b7d60e6469c38b9c16436a7a472d57d9b8562)
- update copyright year [`f5cb4ce`](https://github.com/ImageMagick/ImageMagick6/commit/f5cb4ce9319066b5b4740f725d9f0f8a52368be8)
- ... [`e29fbed`](https://github.com/ImageMagick/ImageMagick6/commit/e29fbed480a847fd70671ffb445769cc07f87b40)
- Removed methods that have been renamed. [`88f63de`](https://github.com/ImageMagick/ImageMagick6/commit/88f63de88c6242bfdbb669b90f44c1827f71aebf)
- https://github.com/ImageMagick/ImageMagick/issues/4828 [`37ac2f0`](https://github.com/ImageMagick/ImageMagick6/commit/37ac2f0185a2afc88de705937f1e1e57004aa6ba)
- Fixed build error. [`8cb3ec3`](https://github.com/ImageMagick/ImageMagick6/commit/8cb3ec3f676b7b566f0590536894f11fac6cf8b4)

## [6.9.12-38](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-37...6.9.12-38) - 2022-02-05

### Commits

- ... [`0ec8137`](https://github.com/ImageMagick/ImageMagick6/commit/0ec813759359a1a9f4e37a1696bb2f967c917776)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=44424 [`bbf05a3`](https://github.com/ImageMagick/ImageMagick6/commit/bbf05a3449db3555cc05f4f3cacf172d6a0d35cc)
- https://github.com/ImageMagick/ImageMagick/issues/4793 [`dd65574`](https://github.com/ImageMagick/ImageMagick6/commit/dd655741bb71f7a129757fc0676e8aa328b44dad)
- ... [`c726d86`](https://github.com/ImageMagick/ImageMagick6/commit/c726d861a67aadf697eb35b8847f6431b47dec1e)
- release [`b5bb28a`](https://github.com/ImageMagick/ImageMagick6/commit/b5bb28a0ca2e53b668e4057a0cb04166ef781793)
- pending release [`fa0b758`](https://github.com/ImageMagick/ImageMagick6/commit/fa0b758566ef994436fc9d9c14b68b433e2dd513)
- avoid deep recursion [`513854d`](https://github.com/ImageMagick/ImageMagick6/commit/513854d34c8e505207c4c4a4cb0932ef7770fa05)
- Corrected setting delay. [`bd7f6d7`](https://github.com/ImageMagick/ImageMagick6/commit/bd7f6d781953b415e7d5f4830feebbe87a54e62f)
- VID images not permitted when compositing [`f4529c0`](https://github.com/ImageMagick/ImageMagick6/commit/f4529c0dcf3a8f96c438086b28fbef8338cda0b1)
- reference https://github.com/ImageMagick/ImageMagick/issues/4807 [`f2ee9a7`](https://github.com/ImageMagick/ImageMagick6/commit/f2ee9a74d52794b4ef9e62e71d4906d5cab9ef27)
- https://github.com/ImageMagick/ImageMagick/issues/4807 [`bcbcfeb`](https://github.com/ImageMagick/ImageMagick6/commit/bcbcfeb3b697e8ec1a105dc7c7099f5f9191f172)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=44401 [`e94e616`](https://github.com/ImageMagick/ImageMagick6/commit/e94e616aff39358e09d6ae3180baf3cb59923690)
- check if image extent is NaN [`0608714`](https://github.com/ImageMagick/ImageMagick6/commit/0608714e4b8df32180359ba502990693ccfe3115)

## [6.9.12-37](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-36...6.9.12-37) - 2022-01-29

### Commits

- permit compositing MPRI images [`4dd4d0d`](https://github.com/ImageMagick/ImageMagick6/commit/4dd4d0df449acb13fb859041b4996af58243e352)
- bump patch level version [`e662b69`](https://github.com/ImageMagick/ImageMagick6/commit/e662b69dd2cb3209339aff3c277493ef18f72a92)
- pending release [`f0b31c1`](https://github.com/ImageMagick/ImageMagick6/commit/f0b31c169c00ad9e688b89e6a17e2678cc91c733)
- check for excessive color name length [`1025a9b`](https://github.com/ImageMagick/ImageMagick6/commit/1025a9b0373dd194fc4529424e80396f35b1bbf4)
- pending release [`f1e0995`](https://github.com/ImageMagick/ImageMagick6/commit/f1e09958774501f6e39e4b06deed0c351b8158ca)
- restore MPRI URI [`d624f7f`](https://github.com/ImageMagick/ImageMagick6/commit/d624f7f008450eded4f006517e3275647eb69864)

## [6.9.12-36](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-35...6.9.12-36) - 2022-01-28

### Commits

- check for excessive memory request when drawing [`50aeffe`](https://github.com/ImageMagick/ImageMagick6/commit/50aeffee5b880716bc3fbca6edf990a853b04a4d)
- https://github.com/ImageMagick/ImageMagick/issues/4766 [`77fc0b9`](https://github.com/ImageMagick/ImageMagick6/commit/77fc0b952bf505ff10b5abb94b33206f31056e06)
- It's a new dawn; It's a new day; It's a new life; For ImageMagick [`49ea804`](https://github.com/ImageMagick/ImageMagick6/commit/49ea804be9295c12b457843271042e2e3521750e)
- promote blocksize from int to ssize_t [`ba2e0ef`](https://github.com/ImageMagick/ImageMagick6/commit/ba2e0efa42a0ac656fa4b01beb6500915ee11bcd)
- pending release [`fee44f7`](https://github.com/ImageMagick/ImageMagick6/commit/fee44f7b445cdca56a5ec19a2878608a511098c9)
- pending release [`fca98f0`](https://github.com/ImageMagick/ImageMagick6/commit/fca98f0ad524641afd5f0c4bf42852ebaf8c1c27)
- ... [`1ac7d3d`](https://github.com/ImageMagick/ImageMagick6/commit/1ac7d3da9c45ee15ef7421d3ae62943f72f3cdab)
- pending release [`44065d3`](https://github.com/ImageMagick/ImageMagick6/commit/44065d3e7ede7012ab32bb560d838eed9507720d)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=43967 [`f5f594a`](https://github.com/ImageMagick/ImageMagick6/commit/f5f594abe588bcc6ee870998bc801ede67e5b8b5)
- PDF unicode title [`bf36be4`](https://github.com/ImageMagick/ImageMagick6/commit/bf36be46887cdc65c8add8c6bfed20a0c4ae290d)
- https://github.com/ImageMagick/ImageMagick/issues/4771 [`8e326c6`](https://github.com/ImageMagick/ImageMagick6/commit/8e326c63f27c544e1dbbb1a329256306e93f1a70)
- Added missing version check. [`9cfea23`](https://github.com/ImageMagick/ImageMagick6/commit/9cfea235600550f02b2df61c276c438ab031441e)

## [6.9.12-35](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-34...6.9.12-35) - 2022-01-22

### Commits

- https://github.com/ImageMagick/ImageMagick/issues/4629 [`dea9fb3`](https://github.com/ImageMagick/ImageMagick6/commit/dea9fb319c9f4564662e0f1705856854aec01605)
- Build ImageMagick on Windows with VisualStudio 2022 instead. [`a9b405b`](https://github.com/ImageMagick/ImageMagick6/commit/a9b405b9e1bd219351d8961c9ccfddbc2a299d3a)
- Use same checks as in IM7. [`a93c000`](https://github.com/ImageMagick/ImageMagick6/commit/a93c000f4585e9ef3b0a8a8f55bdcc25575e21b7)
- permit 4GB blocks [`23b4299`](https://github.com/ImageMagick/ImageMagick6/commit/23b42998f5b3345d1915d4222cc2e858badca639)
- ... [`e8b78e7`](https://github.com/ImageMagick/ImageMagick6/commit/e8b78e7bae67150667f3037932d0b3f1bc00434d)
- improved fix for possible DoS for certain SVG constructs [`84ec305`](https://github.com/ImageMagick/ImageMagick6/commit/84ec30550c3146f525383f18a786a6bbd5028a93)
- https://github.com/ImageMagick/ImageMagick/issues/4704 [`25c9e4d`](https://github.com/ImageMagick/ImageMagick6/commit/25c9e4df716f34519d346369892b030ee5155312)
- https://github.com/ImageMagick/ImageMagick/issues/4704 [`9002280`](https://github.com/ImageMagick/ImageMagick6/commit/90022807243230deea06b9dcc874d2a41c611631)
- AVIF is supported by the HEIC coder [`2287dca`](https://github.com/ImageMagick/ImageMagick6/commit/2287dca493099e423ca751bf55a3f114fc848a96)
- https://github.com/ImageMagick/ImageMagick/issues/4639 [`2318bfb`](https://github.com/ImageMagick/ImageMagick6/commit/2318bfb4009f8742b4c09007f3c8ba72bac7bf89)
- eliminate C++ compiler warnings [`08dd651`](https://github.com/ImageMagick/ImageMagick6/commit/08dd6515f47bf4276797b46b9c81e016c7c46993)
- Removed comment. [`f5bac9b`](https://github.com/ImageMagick/ImageMagick6/commit/f5bac9b20849fc7c540550e15f3ae839faf506fb)
- https://github.com/ImageMagick/ImageMagick/issues/4681 [`21bddc2`](https://github.com/ImageMagick/ImageMagick6/commit/21bddc28dcc31dde7d23b25009e1efbedcbae174)
- Added checks for invalid PSD channel size. [`e26d718`](https://github.com/ImageMagick/ImageMagick6/commit/e26d718edaf73793c7a0f2f609ecf662fcccd562)
- revert [`dada640`](https://github.com/ImageMagick/ImageMagick6/commit/dada640f2732a4ae8e524ac95c1b998cf0102a80)
- eliminate rare memory leak [`cf21bd4`](https://github.com/ImageMagick/ImageMagick6/commit/cf21bd4a4dd173a156c529082b6eb074c6aced71)
- https://github.com/ImageMagick/ImageMagick/issues/4654 [`aee3f00`](https://github.com/ImageMagick/ImageMagick6/commit/aee3f004aa62bafb20dcb7c7c0675ee7d5bf9255)
- Changed the build of configure to 64-bit. [`f5cb4bb`](https://github.com/ImageMagick/ImageMagick6/commit/f5cb4bb894806c595b08591f7ff755caed117fe6)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=43390 [`2ff94fa`](https://github.com/ImageMagick/ImageMagick6/commit/2ff94fab76c89707ed241d3a85e3881d88d1b032)
- ... [`bbb86a2`](https://github.com/ImageMagick/ImageMagick6/commit/bbb86a2c59fabc73d0262c70ae71ce80a89b4c5e)
- zero papersize geometry [`4382359`](https://github.com/ImageMagick/ImageMagick6/commit/4382359ee5d87266c25646f68da20d4229d771bd)
- https://github.com/ImageMagick/ImageMagick/issues/4679 [`8854349`](https://github.com/ImageMagick/ImageMagick6/commit/88543494464bf94ef3430ba33bb34c62ba5050d6)
- pending release [`aff974e`](https://github.com/ImageMagick/ImageMagick6/commit/aff974eb0da8eaee7edf3acbe945a2d8bb4a4c8e)
- https://github.com/ImageMagick/ImageMagick/issues/4660 [`fd1df0b`](https://github.com/ImageMagick/ImageMagick6/commit/fd1df0b69806c4d820c277759b5171795502dd70)
- ... [`f7a43f3`](https://github.com/ImageMagick/ImageMagick6/commit/f7a43f3552a6f47a1258a524ec8ed33250601839)
- Fixed possible memory leak. [`e5bee23`](https://github.com/ImageMagick/ImageMagick6/commit/e5bee2335ec13cff0171e9517f862298bb7f0c0a)
- Fixed Windows build. [`e838900`](https://github.com/ImageMagick/ImageMagick6/commit/e838900d9380feba6900adc7537eea852cd478d5)
- cosmetic [`623e681`](https://github.com/ImageMagick/ImageMagick6/commit/623e6813fcfe68729d78cc27b4d9bc77a678c760)
- pending release [`d02bc00`](https://github.com/ImageMagick/ImageMagick6/commit/d02bc0072070ef2f33ee6d8acca436a720b9861b)
- fuzzy equality check [`0256b55`](https://github.com/ImageMagick/ImageMagick6/commit/0256b550e7fd2bcec82802f4c349f6e64ad1d06a)
- revert [`46859fd`](https://github.com/ImageMagick/ImageMagick6/commit/46859fda719f814ec7e1fbbc37ed66b6706d4094)
- ... [`a4d1e39`](https://github.com/ImageMagick/ImageMagick6/commit/a4d1e399130e50698cb1210e95224f7cd301ba8d)
- Added move to use the installed version of Strawberry Perl instead. [`d68e6fa`](https://github.com/ImageMagick/ImageMagick6/commit/d68e6faf1d817c9b4db97b1643226dfce2a90dfc)
- Allow workflow dispatch. [`809c4ce`](https://github.com/ImageMagick/ImageMagick6/commit/809c4cefefea926887e17f63093a98223c62d857)

## [6.9.12-34](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-33...6.9.12-34) - 2021-12-22

### Commits

- ... [`39b8934`](https://github.com/ImageMagick/ImageMagick6/commit/39b8934f42179a4a79b41d3fa141b8fac7064ea2)
- Set the colorspace after the width and height of the image have been checked. [`3fd8496`](https://github.com/ImageMagick/ImageMagick6/commit/3fd8496d027b4b03e622cbf093e0b28d1e30d4ac)
- https://github.com/ImageMagick/ImageMagick/issues/4626 [`c10351c`](https://github.com/ImageMagick/ImageMagick6/commit/c10351c16b8d2cabd11d2627a02de522570f6ceb)
- ... [`8093989`](https://github.com/ImageMagick/ImageMagick6/commit/8093989a6bf0ea36a2e81d61400e47c9cdba3032)
- check for unbalanced parenthesis [`6fdd03b`](https://github.com/ImageMagick/ImageMagick6/commit/6fdd03b7fef68cfdb1c0f87d5e0e72a29f2d0336)
- pending release [`0b0cbf7`](https://github.com/ImageMagick/ImageMagick6/commit/0b0cbf7b0f5c2ddcd41c85fc2da64d4771f80018)
- Corrected method call. [`05259b5`](https://github.com/ImageMagick/ImageMagick6/commit/05259b51165aa26f9ec265e201315391a5a958b4)

## [6.9.12-33](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-32...6.9.12-33) - 2021-12-18

### Commits

- Swapped the Sync8BimProfile and the SyncExifProfile methods. [`77b718c`](https://github.com/ImageMagick/ImageMagick6/commit/77b718c3f5d5e39710d227f2bb6a7fb65abd4c57)
- ... [`3deb899`](https://github.com/ImageMagick/ImageMagick6/commit/3deb89958f6787deca910570ff5fb8d27210b554)
- Improved adjustment of page offset when resizing an image. [`accf336`](https://github.com/ImageMagick/ImageMagick6/commit/accf33670091ef833b45ef5bb913812e16469333)
- https://github.com/ImageMagick/ImageMagick/issues/4558 [`fb428af`](https://github.com/ImageMagick/ImageMagick6/commit/fb428af466701e487cfd0f657c78e1f74da4c12b)
- Also sync the exif profile inside the 8bim profile. [`3be80bc`](https://github.com/ImageMagick/ImageMagick6/commit/3be80bc9c9b5e49a6266b680e38d39d5ecaeaadb)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=42504 [`9f7310b`](https://github.com/ImageMagick/ImageMagick6/commit/9f7310b7a3c80f132c548ffb8f29eea7dabae8c2)
- https://github.com/ImageMagick/ImageMagick/issues/4587 [`526a3d1`](https://github.com/ImageMagick/ImageMagick6/commit/526a3d19790b753e4d7f63515dc667a3472f9eda)
- improved adjustment of page offset when resizing an image [`c8bb427`](https://github.com/ImageMagick/ImageMagick6/commit/c8bb4278eb7be195cc45ba08e617987cf34dad1e)
- revert [`7cbce51`](https://github.com/ImageMagick/ImageMagick6/commit/7cbce514e6a0f530b5f50b960f6d95c62c9416f5)
- https://github.com/ImageMagick/ImageMagick/security/code-scanning/31 [`094e143`](https://github.com/ImageMagick/ImageMagick6/commit/094e143714873a2903093ea6c128af267ef8c997)
- pending release [`a518f31`](https://github.com/ImageMagick/ImageMagick6/commit/a518f310bc77991712a53f6984f9f0edce706174)
- Corrected method name. [`15aadb7`](https://github.com/ImageMagick/ImageMagick6/commit/15aadb7691a3a8cd47cbbae9ca3ec58c01acc3c3)
- Corrected the built-in video encoder and decoder. [`91320cc`](https://github.com/ImageMagick/ImageMagick6/commit/91320cc53f6c5e8b59b5e22e0042d62b230344ba)
- Restored debug message. [`2ab41fb`](https://github.com/ImageMagick/ImageMagick6/commit/2ab41fbf336faf0fbb9d3217b72c6f6336b7767b)
- ... [`add9cb1`](https://github.com/ImageMagick/ImageMagick6/commit/add9cb14e14eef02806715d97abcf5d04a3e55dd)
- Corrected typecast. [`87ce0d8`](https://github.com/ImageMagick/ImageMagick6/commit/87ce0d8fa8446b142938f1be63cf3e6b866697cf)

## [6.9.12-32](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-31...6.9.12-32) - 2021-12-04

### Commits

- ... [`60be1a6`](https://github.com/ImageMagick/ImageMagick6/commit/60be1a6c9698fc970c087b5384da19829b8fb386)
- https://github.com/ImageMagick/ImageMagick/issues/4501 [`936332e`](https://github.com/ImageMagick/ImageMagick6/commit/936332e6b6a5e6105f02b2d9232bcbeafa681eb3)
- revert memory leak patch [`e735d88`](https://github.com/ImageMagick/ImageMagick6/commit/e735d88c251a4c7ef60c39ae3322fc7b4cbb50f9)
- https://github.com/ImageMagick/ImageMagick/issues/4501 [`fa5c3aa`](https://github.com/ImageMagick/ImageMagick6/commit/fa5c3aa6c111b8c4c83d945e992da95200dbdba6)
- https://github.com/ImageMagick/ImageMagick/issues/4512 [`4c0fcf3`](https://github.com/ImageMagick/ImageMagick6/commit/4c0fcf39fd51f2c89832767e1befaeda7ff86097)
- Added missing checks for the return value of the exr methods. [`5beeab8`](https://github.com/ImageMagick/ImageMagick6/commit/5beeab8a1297dbae1f05f88aeffe26278b744a6f)
- ASAN returns false positives for OMP [`976dba6`](https://github.com/ImageMagick/ImageMagick6/commit/976dba67f1a4352d838a2a9f823812892f8230b5)
- ... [`c611e8f`](https://github.com/ImageMagick/ImageMagick6/commit/c611e8f5102bbcf20ac0a4fd3e7e719779c60fd9)
- Added check for invalid size. [`94f76dd`](https://github.com/ImageMagick/ImageMagick6/commit/94f76dd2f760241bec51e7d66873e77a58d812ba)
- https://github.com/ImageMagick/ImageMagick/issues/4501 [`2a29e35`](https://github.com/ImageMagick/ImageMagick6/commit/2a29e35480271e14a0961492867e9d246e64cc05)
- pending release [`be1bc1d`](https://github.com/ImageMagick/ImageMagick6/commit/be1bc1d9650b4530a037d7c2d58d1a5a4b73f04e)
- pending release [`b5525d6`](https://github.com/ImageMagick/ImageMagick6/commit/b5525d640ea48befa9cfb4e154672d4076f06aec)
- pending release [`3bf73bf`](https://github.com/ImageMagick/ImageMagick6/commit/3bf73bf7e3f846dd6d3e20b843e8a34e8f4f7589)
- https://github.com/ImageMagick/ImageMagick/issues/4535 [`9a7d07d`](https://github.com/ImageMagick/ImageMagick6/commit/9a7d07d8b22098210a47cabb99cb58de599bb5ba)
- pending release [`1832b1d`](https://github.com/ImageMagick/ImageMagick6/commit/1832b1d334ca00e66ad6ff5f115750692cb6b3b7)
- pending release [`9e8e460`](https://github.com/ImageMagick/ImageMagick6/commit/9e8e460e7ef26ab6f5666c7292f7b82752a09b7d)
- eliminate compiler warning [`63f5b43`](https://github.com/ImageMagick/ImageMagick6/commit/63f5b4329181e70cff1a646229dc3b3ba5a40d69)
- https://github.com/ImageMagick/ImageMagick/discussions/4529 [`e35c98c`](https://github.com/ImageMagick/ImageMagick6/commit/e35c98c5ab111284b198d0022ed479d0e6ecef3c)
- close input file if early exit on exception [`fd51385`](https://github.com/ImageMagick/ImageMagick6/commit/fd513853ac20e6ae784a795fff41cacfe8b54e73)

## [6.9.12-31](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-30...6.9.12-31) - 2021-11-21

### Commits

- ... [`9e6a637`](https://github.com/ImageMagick/ImageMagick6/commit/9e6a63782e4d22786b82b1db6575181724fdb4f1)
- Corrected OpenCL define checks. [`149fb8a`](https://github.com/ImageMagick/ImageMagick6/commit/149fb8a345ccb58cc70d3252be5d0f7cf6850d64)
- pending release [`4976493`](https://github.com/ImageMagick/ImageMagick6/commit/49764932cdb7e0ac966828ce15a819d85ccbeae3)
- Removed unnecessary define. [`6722a79`](https://github.com/ImageMagick/ImageMagick6/commit/6722a798f2b4385a293555675be8967890448b38)
- eliminate possible divide by zero [`8c80027`](https://github.com/ImageMagick/ImageMagick6/commit/8c80027ca8d6c84c3ed815059bbf353eb8dc2d58)

## [6.9.12-30](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-29...6.9.12-30) - 2021-11-20

### Commits

- https://github.com/ImageMagick/ImageMagick6/issues/168 [`9a70911`](https://github.com/ImageMagick/ImageMagick6/commit/9a70911bc8b3c6f3a49bb54766cfba0e69f2a2fe)
- ... [`3b2a005`](https://github.com/ImageMagick/ImageMagick6/commit/3b2a005a5a58698d9cb99e48d46ce19d19abfd39)
- mitigate UBSAN alerts [`1219eac`](https://github.com/ImageMagick/ImageMagick6/commit/1219eac5d3bfb796753597f37412df567f629c08)
- check for NULL index channel [`f63a211`](https://github.com/ImageMagick/ImageMagick6/commit/f63a2117ba05da426d996c0aee92e5b0c7b1f852)
- eliminate compiler warning [`7864d48`](https://github.com/ImageMagick/ImageMagick6/commit/7864d48ddb52c490484a890eea21717cab01c61c)
- check if indexes are null [`23bd057`](https://github.com/ImageMagick/ImageMagick6/commit/23bd0570ebb0b845aa62e0c66dd7d822594201ea)
- https://github.com/ImageMagick/ImageMagick6/issues/168 [`7599dd9`](https://github.com/ImageMagick/ImageMagick6/commit/7599dd92e8ad19993a2eb27a2b5103d853bce57f)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=41172 [`5f77de4`](https://github.com/ImageMagick/ImageMagick6/commit/5f77de42c37c184e6db6bbbad52a34070c5a7a2d)
- check for NULL indexes [`e008625`](https://github.com/ImageMagick/ImageMagick6/commit/e00862551327e0b2c4362d6d8f1b78bb4f3496af)
- check for NULL indexes [`3644f40`](https://github.com/ImageMagick/ImageMagick6/commit/3644f40f41d1bf1134e1d6fcd1f227436d045945)
- pending release [`1864067`](https://github.com/ImageMagick/ImageMagick6/commit/1864067f7083a965bc4c4f3ac36ab6976d80a831)
- less aggressive sanity check [`dda7d0b`](https://github.com/ImageMagick/ImageMagick6/commit/dda7d0bb7d4f675f652fea20dff66778fb2bc88b)
- https://github.com/ImageMagick/ImageMagick/issues/4495 [`d46d0c6`](https://github.com/ImageMagick/ImageMagick6/commit/d46d0c647aa67bcfffec5dbd456c24b9c66de66e)
- destroy image list rather than just the first image [`c42cd7c`](https://github.com/ImageMagick/ImageMagick6/commit/c42cd7c143e501aff4d624a2591e7f26ee5d5ce9)
- mitigate UBSAN alerts [`a4dec0c`](https://github.com/ImageMagick/ImageMagick6/commit/a4dec0cbdeb1ed2acf79e8efe664cdb2348e524b)
- mitigate UBSAN alerts [`99841ed`](https://github.com/ImageMagick/ImageMagick6/commit/99841edc96458bad24754b587de79693da67224b)
- pending release [`506ae2c`](https://github.com/ImageMagick/ImageMagick6/commit/506ae2c2e2d4bbb07d4ba4075d06aadccbc675fd)

## [6.9.12-29](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-28...6.9.12-29) - 2021-11-14

### Commits

- latest docs [`f624d40`](https://github.com/ImageMagick/ImageMagick6/commit/f624d406e79ce1d5f600a1ff569bf02d6eccf4b2)
- Use CheckMergedImageAlpha when layer size is zero. [`b614db7`](https://github.com/ImageMagick/ImageMagick6/commit/b614db76102d0f4c38149d2b6c63e091bc975b6b)
- early exit on exception [`b272aca`](https://github.com/ImageMagick/ImageMagick6/commit/b272acab91444f2115099fe51ee6c91bb4db5d50)
- Improved detection of %%. [`cddc5be`](https://github.com/ImageMagick/ImageMagick6/commit/cddc5be6a7150e9c47fd155b402fc896e1d9d0b6)
- ... [`c66229f`](https://github.com/ImageMagick/ImageMagick6/commit/c66229fb1a73213f392752050d49084d32032aec)
- ... [`8867bad`](https://github.com/ImageMagick/ImageMagick6/commit/8867bada8703071aa5356240d677b2ac1069ff3e)
- Corrected detection of the CMYK colorspace. [`af56076`](https://github.com/ImageMagick/ImageMagick6/commit/af56076082b5703d65f754a501876d082743a0ab)
- https://github.com/ImageMagick/ImageMagick/issues/4452 [`ba084f6`](https://github.com/ImageMagick/ImageMagick6/commit/ba084f6bda2edbacf1df824bb214728234ffaa86)
- pending release [`efe0cae`](https://github.com/ImageMagick/ImageMagick6/commit/efe0caec013e87837c29a83e57e5ea7397ce8645)
- pending release [`4dbdd3b`](https://github.com/ImageMagick/ImageMagick6/commit/4dbdd3bd7d4cb95bc883010d70d0e31d69308536)
- ... [`4efb23e`](https://github.com/ImageMagick/ImageMagick6/commit/4efb23ee93a2026434e5b0253ddb9c3622c1b1ab)
- ... [`04c02b3`](https://github.com/ImageMagick/ImageMagick6/commit/04c02b3ad4ae57a28c87a094fd72f153b6dc49bb)

## [6.9.12-28](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-27...6.9.12-28) - 2021-10-29

### Commits

- pending release [`0ca0004`](https://github.com/ImageMagick/ImageMagick6/commit/0ca000449de02d87e3fccba10255472417a4d3dc)
- ... [`4b5c30c`](https://github.com/ImageMagick/ImageMagick6/commit/4b5c30c0b879dc4c670c27f53721df60896724c2)
- ... [`dd1dc33`](https://github.com/ImageMagick/ImageMagick6/commit/dd1dc3392ee1ec775f9d53d2fe306e458dadaef2)
- ... [`e10fc76`](https://github.com/ImageMagick/ImageMagick6/commit/e10fc76ab4c7850547271a73d1b1c7ebebb691be)
- pending release [`af2ee30`](https://github.com/ImageMagick/ImageMagick6/commit/af2ee30d2201829812864d7d8aadee0e46cd5d91)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=40451 [`ba7e11c`](https://github.com/ImageMagick/ImageMagick6/commit/ba7e11c5ea554317c28977ff6e5afc4f050a7ae1)
- Fix stack overflow when parsing malicious ps image file. [`f74b2b1`](https://github.com/ImageMagick/ImageMagick6/commit/f74b2b19d13df6b61b5ede33aa7249dcb0f496a5)
- pending release [`1898d52`](https://github.com/ImageMagick/ImageMagick6/commit/1898d52023601f8ea5bdb583f9dd2b3a435572cb)
- pending release [`f59af4f`](https://github.com/ImageMagick/ImageMagick6/commit/f59af4f713acf87b7279e68c01ac9579fea8793a)
- cosmetic [`d480691`](https://github.com/ImageMagick/ImageMagick6/commit/d480691c7d0ad3f16ff94148e781cbaff05ed1be)

## [6.9.12-27](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-26...6.9.12-27) - 2021-10-25

### Commits

- ... [`60fcc24`](https://github.com/ImageMagick/ImageMagick6/commit/60fcc24991c45628286b8a88ccd5983d4979626d)
- pending release [`b6fe79f`](https://github.com/ImageMagick/ImageMagick6/commit/b6fe79f95ebd91a0439cbb7adb4602c4d4aa154e)

## [6.9.12-26](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-25...6.9.12-26) - 2021-10-24

### Commits

- https://github.com/ImageMagick/ImageMagick/issues/4379 [`199a858`](https://github.com/ImageMagick/ImageMagick6/commit/199a8586fd1ab273b25dae3f75ff131f4b302ceb)
- https://github.com/ImageMagick/ImageMagick/issues/4378 [`c661299`](https://github.com/ImageMagick/ImageMagick6/commit/c661299cd1ff36d8783641cb4cffdffb0fd9041d)
- adjust metrics is no longer sensitive to gravity [`6dc9251`](https://github.com/ImageMagick/ImageMagick6/commit/6dc9251f0dcc11d29dbb90f430431b553df46f35)
- :1 [`cc76510`](https://github.com/ImageMagick/ImageMagick6/commit/cc765107a9c7e19607e7fd18feb89a22a563ebb4)
- Revert adjustment of the y1 value [`122366e`](https://github.com/ImageMagick/ImageMagick6/commit/122366e570731f71c90e82f219c43d78864597a3)
- Corrected versions in ChangeLog. [`7e972cc`](https://github.com/ImageMagick/ImageMagick6/commit/7e972cc7157ddaf638c8301945058970af0c114f)
- https://oss-fuzz.com/testcase-detail/6308942275805184 [`5c82207`](https://github.com/ImageMagick/ImageMagick6/commit/5c822075c884a488242d8d5558964a087cc9db99)
- eliminate compiler warning [`8afbdbc`](https://github.com/ImageMagick/ImageMagick6/commit/8afbdbc36fe128383b4fce3374c080ac34177b15)
- fix stack overflow when parsing malicious tiff image [`85a370c`](https://github.com/ImageMagick/ImageMagick6/commit/85a370c79afeb45a97842b0959366af5236e9023)
- https://github.com/ImageMagick/ImageMagick/issues/4372 [`2466e9a`](https://github.com/ImageMagick/ImageMagick6/commit/2466e9a94e42b2511ef7016259a72a714808f9fe)
- ... [`c4b9474`](https://github.com/ImageMagick/ImageMagick6/commit/c4b94746cb97fc81b0b552e14f4e462449e567b5)
- pending release [`a85dee3`](https://github.com/ImageMagick/ImageMagick6/commit/a85dee3187419ab8c8dc1385b0be9bd9c51c731c)
- revert optimization [`07c8384`](https://github.com/ImageMagick/ImageMagick6/commit/07c838431ab2cd620daf1d43e35f8a3f0b23b7a5)
- slight performance optimization [`627cf43`](https://github.com/ImageMagick/ImageMagick6/commit/627cf4307b93d5185fe877db8ebb51236043f350)
- pending release [`adf4467`](https://github.com/ImageMagick/ImageMagick6/commit/adf446722724ea7cad8ebc6046e87df82aae4f05)
- ... [`7671137`](https://github.com/ImageMagick/ImageMagick6/commit/76711376db504e9c786426e9381021889b00590e)
- pending release [`fd247de`](https://github.com/ImageMagick/ImageMagick6/commit/fd247de75a1f271474294cc97c09f291e58f2be3)
- Correct more version numbers. [`b0a8b26`](https://github.com/ImageMagick/ImageMagick6/commit/b0a8b2655487ee5b6248897e5c955b8a44bfc790)
- pending release [`175f33e`](https://github.com/ImageMagick/ImageMagick6/commit/175f33e13311562f51ae7b1631af65bb0ee29676)
- pending release [`3430fb8`](https://github.com/ImageMagick/ImageMagick6/commit/3430fb87b5714e3d50717497be71a0531600da76)
- test release [`01e79c2`](https://github.com/ImageMagick/ImageMagick6/commit/01e79c207608bb7eacd4b6710663213773684dcd)
- ... [`6fe9741`](https://github.com/ImageMagick/ImageMagick6/commit/6fe9741ec186b9893bc87d39e83d0d705fe0fad5)

## [6.9.12-25](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-24...6.9.12-25) - 2021-10-10

### Commits

- https://github.com/ImageMagick/ImageMagick/discussions/4311 [`f6fdd03`](https://github.com/ImageMagick/ImageMagick6/commit/f6fdd03216d401b7e3b558218f7805b61d2cecc5)
- don't adjust metrics if gravity is undefined [`79c537c`](https://github.com/ImageMagick/ImageMagick6/commit/79c537c7bdfe0f71b4354ace4d9c9976c29b4c4a)
- ... [`cfcd23e`](https://github.com/ImageMagick/ImageMagick6/commit/cfcd23ee92152228ba36ac12d6fc0a6ec34d41c0)
- Moved using namespace std after ImageMagick header files to fix issues when enabling ISO C++ 17 and ISO C17 [`2c96ab5`](https://github.com/ImageMagick/ImageMagick6/commit/2c96ab5d098fcf3d2002378355bc2ad3eaccaddf)
- ... [`24961a9`](https://github.com/ImageMagick/ImageMagick6/commit/24961a9e25ac31b7ddd42eb8f1c130717971da16)
- fix ANSI compiler error [`94119fe`](https://github.com/ImageMagick/ImageMagick6/commit/94119febc83c74913017289e5060e1e5ccf378d4)
- https://github.com/ImageMagick/ImageMagick/issues/4314 [`c8bba5b`](https://github.com/ImageMagick/ImageMagick6/commit/c8bba5bf458c63486417c6f0084ce383c89d78b1)
- pending release [`af67f12`](https://github.com/ImageMagick/ImageMagick6/commit/af67f1234b95fcad2fc28560fb8136defc16108a)
- ... [`48e52d0`](https://github.com/ImageMagick/ImageMagick6/commit/48e52d0ef0ce365a5a6e7c4d20cff582be835786)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=39708 [`5569c6c`](https://github.com/ImageMagick/ImageMagick6/commit/5569c6cc38ea99d9cba667deaddf09ba1ec42005)

## [6.9.12-24](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-23...6.9.12-24) - 2021-10-03

### Commits

- Adjust the x1 offset of the bounds to make sure a font is rendered inside the canvas. [`1746362`](https://github.com/ImageMagick/ImageMagick6/commit/17463624f35b293f5e1689b8039bcdae96bdd8d1)
- ignore zero-length profiles [`94cc6fd`](https://github.com/ImageMagick/ImageMagick6/commit/94cc6fd1c2f3ad739903726ec7e63d31a2b3d747)
- Correct replacement of spaces that use more than one octet. [`1d59719`](https://github.com/ImageMagick/ImageMagick6/commit/1d597191bd1f45d05ff041c89b7e3f8759e9eaf5)
- https://github.com/ImageMagick/ImageMagick/discussions/4227 [`1c5e41a`](https://github.com/ImageMagick/ImageMagick6/commit/1c5e41a934fd40ce86f37ecee6b54a6940183f1e)
- ... [`f4277c4`](https://github.com/ImageMagick/ImageMagick6/commit/f4277c460e804659535de8e2d8dd9507ab50bb2f)
- Revert patch because this breaks font rendering for other fonts. [`c55ddb1`](https://github.com/ImageMagick/ImageMagick6/commit/c55ddb1d646b1540afafd918be89eef69d83b467)
- https://github.com/ImageMagick/ImageMagick/issues/4278 [`4748ccc`](https://github.com/ImageMagick/ImageMagick6/commit/4748ccc31888db1e8610084b611710e7e2dadbfe)
- Correction of the bounds measurements. [`fd9443b`](https://github.com/ImageMagick/ImageMagick6/commit/fd9443b46cb0254f1a6908be2738950d402169ab)
- pending release [`c15d3ae`](https://github.com/ImageMagick/ImageMagick6/commit/c15d3aef8ffe50174763ef00c5780e3d6c774232)
- Added extra check to prevent replacing a non-breaking space with a newline. [`6e82f6f`](https://github.com/ImageMagick/ImageMagick6/commit/6e82f6f182f585ecc1cc70cd3fe7c5adb6c6c5ea)
- cosmetic [`d2b4807`](https://github.com/ImageMagick/ImageMagick6/commit/d2b4807f8eefb98f150901f941f6a1eea892f867)
- Silence warning. [`32bda8b`](https://github.com/ImageMagick/ImageMagick6/commit/32bda8bb2132fad29eb6e175d3da92e45f9c25af)
- Space pointer was still pointing to the old string. [`96f65f4`](https://github.com/ImageMagick/ImageMagick6/commit/96f65f410afee03d45563c5a5fe01f4496d9b581)
- Use same code as IM7. [`770902f`](https://github.com/ImageMagick/ImageMagick6/commit/770902feba3806065e77e477d3b796a185e23a82)
- argument is const [`4137ebc`](https://github.com/ImageMagick/ImageMagick6/commit/4137ebce1e559a483bb50c6aab283a30a938d63d)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=39091 [`a96f221`](https://github.com/ImageMagick/ImageMagick6/commit/a96f221bfa150943d0f63b6b44910c9abd8988b2)
- check return status [`cca5a6a`](https://github.com/ImageMagick/ImageMagick6/commit/cca5a6a3f9eacd6c5db570f90dcd3b73a30b2f59)
- Cosmetic. [`7467737`](https://github.com/ImageMagick/ImageMagick6/commit/74677375e48303e8d3355a1cd63bdd5ee0e90269)
- Whitespace. [`d338817`](https://github.com/ImageMagick/ImageMagick6/commit/d3388174b0603040fd78d681fa85cf1080bef493)
- Fixed build error. [`78e0310`](https://github.com/ImageMagick/ImageMagick6/commit/78e03105e90cd4ac5cbe2970a31a13f66c1270bf)
- ... [`92194b2`](https://github.com/ImageMagick/ImageMagick6/commit/92194b2ac097619013e2be312b0121c0f75911a9)

## [6.9.12-23](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-22...6.9.12-23) - 2021-09-18

### Commits

- ... [`a9b45b4`](https://github.com/ImageMagick/ImageMagick6/commit/a9b45b47282987cd0df488ed597e7b95179960c9)
- Don't set the resolution when the cropbox is used. [`de18836`](https://github.com/ImageMagick/ImageMagick6/commit/de18836f1e1ded1395df589e5977c1aa762b486c)
- pending release [`54a7092`](https://github.com/ImageMagick/ImageMagick6/commit/54a70929c2ad8df2321d4b3fc9c7d1b986ddaa2b)
- Added missing null checks. [`c7039d2`](https://github.com/ImageMagick/ImageMagick6/commit/c7039d20a2fe018f041e40459d722188293012c5)
- Give the buffer a proper size instead of "over allocating". [`ecd4719`](https://github.com/ImageMagick/ImageMagick6/commit/ecd4719848da7562d3724e6f1b7bf24d1b72f1fc)
- Added link to advisory. [`bd43241`](https://github.com/ImageMagick/ImageMagick6/commit/bd432413b03d7eb01ad5dcb14127910b7f80ff4c)
- pending release [`4230c6e`](https://github.com/ImageMagick/ImageMagick6/commit/4230c6e6ab33f8ccaff98529284a6285dc10ec61)
- Added missing bom. [`bd9fb58`](https://github.com/ImageMagick/ImageMagick6/commit/bd9fb58de3d9e3847054ccc7ff5caba72cd5877d)
- https://github.com/ImageMagick/ImageMagick/issues/4235 [`eef08cc`](https://github.com/ImageMagick/ImageMagick6/commit/eef08ccf4da69848a6f475806f23711577f62c9e)

## [6.9.12-22](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-21...6.9.12-22) - 2021-09-12

### Commits

- Moved RSVG rendering to a separate method. [`1dc463e`](https://github.com/ImageMagick/ImageMagick6/commit/1dc463eb50f48b9bd4f06530021f4fe52376e5d4)
- Moved MSVG rendering to a separate method. [`a39da2b`](https://github.com/ImageMagick/ImageMagick6/commit/a39da2b112d2f36d78c5d79a821216385be7f8f3)
- Use yaml template instead. [`edf63d3`](https://github.com/ImageMagick/ImageMagick6/commit/edf63d36a7af9468aa07ca2a4c7b9a98db67c1ec)
- Clean up the remaining PDF files if reading one of the files fails. [`3177df6`](https://github.com/ImageMagick/ImageMagick6/commit/3177df671ee3904bdfe09c05d297fa1580253e98)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`9d97e95`](https://github.com/ImageMagick/ImageMagick6/commit/9d97e95150ed3cd7ddfc478248e48b9c0d40f56b)
- Fixed incorrect check when module is used as the domain in policy.xml that would allow the use of a disabled module. [`8cd2fcd`](https://github.com/ImageMagick/ImageMagick6/commit/8cd2fcd33460826628a7590dc3ce74d7785e1598)
- ... [`75e8372`](https://github.com/ImageMagick/ImageMagick6/commit/75e83721e27b60c7354cb3ec58205a9458999dd5)
- check for EOF [`ae88f07`](https://github.com/ImageMagick/ImageMagick6/commit/ae88f07cd31bdbb671270349abdc48d9ca6463fb)
- ... [`a6f6ee2`](https://github.com/ImageMagick/ImageMagick6/commit/a6f6ee269de56892b35ffbc03ab1accb4f593be9)
- Use the correct rights. [`428e685`](https://github.com/ImageMagick/ImageMagick6/commit/428e68597fa904d0bdc133d878e12acd7dc60fa3)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=38401 [`61c3f46`](https://github.com/ImageMagick/ImageMagick6/commit/61c3f4697b2915b10123c11b09f6cf58abe0c07e)
- Added yml to the .editorconfig [`06c089b`](https://github.com/ImageMagick/ImageMagick6/commit/06c089b3fe5438882d54cc2ad4dbc7394b852643)
- check for EOF [`b3bc44a`](https://github.com/ImageMagick/ImageMagick6/commit/b3bc44a3211edfa701075e3a178bb434050bb785)
- Added extra policy check. [`899d06f`](https://github.com/ImageMagick/ImageMagick6/commit/899d06fb1a97083bddda51cc88abc0f79841667e)
- pending release [`83b8cb1`](https://github.com/ImageMagick/ImageMagick6/commit/83b8cb1d99f0f842be50007572c7ecdb588e292d)
- Revert break to make it possible to use and allow list. [`10c0f5b`](https://github.com/ImageMagick/ImageMagick6/commit/10c0f5b31bbea82ebd219a0da201a99a2e874c52)
- Added early exists. [`005af2a`](https://github.com/ImageMagick/ImageMagick6/commit/005af2a1557c8b49bf1116c380435c8064f9f70c)
- Added missing policy checks in RegisterStaticModules. [`69ea558`](https://github.com/ImageMagick/ImageMagick6/commit/69ea5587de17ef89476be47a3cb7f855c0355a74)
- pending release [`be2ebac`](https://github.com/ImageMagick/ImageMagick6/commit/be2ebac260ba43ede0b3beb5820a5d6492c35481)
- Minor optimization when nothing will change. [`bfbf998`](https://github.com/ImageMagick/ImageMagick6/commit/bfbf9988fd9350a6a4da03daa011539204eecdee)
- pending release [`f48b623`](https://github.com/ImageMagick/ImageMagick6/commit/f48b6233e976f56a499a49c55b5f3f26c11451f5)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=38573 [`c4bdacf`](https://github.com/ImageMagick/ImageMagick6/commit/c4bdacff93e145dc1dd282cca3b04127ceb71bf4)
- pending release [`9146746`](https://github.com/ImageMagick/ImageMagick6/commit/9146746f54a24775225e541edc58364ab13e0126)
- https://github.com/ImageMagick/ImageMagick/issues/2579 [`843fd11`](https://github.com/ImageMagick/ImageMagick6/commit/843fd110d7d3b0fa5e00c553290739fde2778ab1)
- Added missing call to ConstrainColormapIndex. [`02ce9e1`](https://github.com/ImageMagick/ImageMagick6/commit/02ce9e1bbba067b2ebcc18d07456a22570cbf5f2)
- Use AllPolicyRights instead. [`b60e171`](https://github.com/ImageMagick/ImageMagick6/commit/b60e17133b982d28816386b83174c2bc06dd39bd)
- Changed build status link [`412d49b`](https://github.com/ImageMagick/ImageMagick6/commit/412d49b2b2a733401a469b7e658a1113e720c550)
- Also set RGB channels when reading the image (#167). [`4282b98`](https://github.com/ImageMagick/ImageMagick6/commit/4282b98eb645351ddf122faa67c94610718595dc)
- Removed newline. [`8cc488a`](https://github.com/ImageMagick/ImageMagick6/commit/8cc488aaca954aa26406678a0032f40561a3c9b4)
- Added donate badge. [`a3d7d3f`](https://github.com/ImageMagick/ImageMagick6/commit/a3d7d3f1926d060f8acb4417deed015a01efad01)
- Removed travis CI link. [`c3b1c13`](https://github.com/ImageMagick/ImageMagick6/commit/c3b1c1334809ad132dddbdfac91618b144fce796)

## [6.9.12-21](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-20...6.9.12-21) - 2021-09-04

### Commits

- Use different values per channel for scale and translate. [`109e236`](https://github.com/ImageMagick/ImageMagick6/commit/109e236860e35212a90b5eb6b93a6662ca208233)
- Use link for the Windows build instructions instead. [`d8da2c5`](https://github.com/ImageMagick/ImageMagick6/commit/d8da2c53bdc4a738017a8ba346ab523935878faa)
- ./configure --help no longer lists -disable-assert twice [`0aab306`](https://github.com/ImageMagick/ImageMagick6/commit/0aab3061aad8211bcec1eb0f4e479414c8a9a3f1)
- ... [`397b5c3`](https://github.com/ImageMagick/ImageMagick6/commit/397b5c32487efdc5eb7daf206c6317fb670bad16)
- https://github.com/ImageMagick/ImageMagick/issues/4105 [`3afc3bc`](https://github.com/ImageMagick/ImageMagick6/commit/3afc3bc9d97ec424bd92ab5c74f090586d91fa0b)
- initialize buffer before calling TIFFGetField() [`ce2f067`](https://github.com/ImageMagick/ImageMagick6/commit/ce2f0676f8766343ae2322ace7311a53c7ae6d97)
- Added .editorconfig [`afad655`](https://github.com/ImageMagick/ImageMagick6/commit/afad65584be6d6d25902599b44f4c20c9a747692)
- Add -HDRI to the quantum in the version string when HDRI is enabled. [`423a801`](https://github.com/ImageMagick/ImageMagick6/commit/423a8014dfa4705ebd8ec057ea78d99c224871d7)
- pending release [`c4ed7a2`](https://github.com/ImageMagick/ImageMagick6/commit/c4ed7a29cf8695a67341175a329532947bc50b54)
- Use UTC date as requested in #166. [`e0967ea`](https://github.com/ImageMagick/ImageMagick6/commit/e0967eae28b4594f08c0a443ee53ac15390cff4a)
- pending release [`9eb3b4e`](https://github.com/ImageMagick/ImageMagick6/commit/9eb3b4ea7b66e515283c0f9b5158c0c2f368c324)
- Minor changes to the formatting of the parentheses. [`278a93e`](https://github.com/ImageMagick/ImageMagick6/commit/278a93e8940eff474a083b42dde39a0c7da1c85e)
- https://github.com/ImageMagick/ImageMagick/issues/4121 [`6ba45df`](https://github.com/ImageMagick/ImageMagick6/commit/6ba45df1e4c67d9897262a7ff5706eb404f2ea7f)
- tweak the bilevel image type [`473c7cd`](https://github.com/ImageMagick/ImageMagick6/commit/473c7cd850bdc40c2d1e8e72c4d3b073f1079138)
- https://oss-fuzz.com/testcase-detail/6502669439598592 [`995de33`](https://github.com/ImageMagick/ImageMagick6/commit/995de330310dd35531165d9471fe4d31e0fa79ae)
- Add -dPrinted=false to the Ghostscript options (#4019) [`5f82ea4`](https://github.com/ImageMagick/ImageMagick6/commit/5f82ea411e7e1190f2f7aed8a0b1c97a42b6bd58)

## [6.9.12-20](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-19...6.9.12-20) - 2021-08-22

### Commits

- check if colorspace is incompatible before transforming it to sRGB [`fdf7e64`](https://github.com/ImageMagick/ImageMagick6/commit/fdf7e64ed09666a0c8f3588b47d302b01a7cdeaa)
- the -format option now respects the -channel argument [`6dc7e94`](https://github.com/ImageMagick/ImageMagick6/commit/6dc7e946ad28bc74f0385f32409382d2c290f6c2)
- mean is already computed, don't compute it again [`b1a8609`](https://github.com/ImageMagick/ImageMagick6/commit/b1a86095382b696ffef5a286b3cdb2ecf1599683)
- ... [`aebaac6`](https://github.com/ImageMagick/ImageMagick6/commit/aebaac62a29393e35d3c20715056cb74f6792e13)
- heap-based buffer overflow in TIFF coder (alert from Hunter Mitchell) [`e1fbcdf`](https://github.com/ImageMagick/ImageMagick6/commit/e1fbcdf3aad96d51db65c1601117396eac665a6d)
- optimize on grayscale detection [`e38fce1`](https://github.com/ImageMagick/ImageMagick6/commit/e38fce1ef0f7b569ec664a4b228335e34e037ae0)
- timeb.h is deprecated [`827ba53`](https://github.com/ImageMagick/ImageMagick6/commit/827ba5310372558385feb91a03afda829928a25e)
- Use new solution that is already upgrade to VS2019. [`b9ca6d9`](https://github.com/ImageMagick/ImageMagick6/commit/b9ca6d96820f7f2278515f6bfb26b72c42e1338b)
- eliminate improper assertion [`78c72ee`](https://github.com/ImageMagick/ImageMagick6/commit/78c72ee91c93c4d10f89de781a711bf4e53dfcd9)
- grayscale images were not being written properly [`84e8b18`](https://github.com/ImageMagick/ImageMagick6/commit/84e8b18294907a1232b216d89a60008341dfbc5a)
- heap-based buffer overflow in TIFF coder (alert from Hunter Mitchell) [`f90a091`](https://github.com/ImageMagick/ImageMagick6/commit/f90a091c7dd12cc53b0999bf49d1c80651534eea)
- reset image structure magick member [`e2045ec`](https://github.com/ImageMagick/ImageMagick6/commit/e2045ec83b5f709decf50c762ceac843e749d52e)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`63037e7`](https://github.com/ImageMagick/ImageMagick6/commit/63037e7bbf33574513126f5aef0acf3416146a93)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`37b4985`](https://github.com/ImageMagick/ImageMagick6/commit/37b49851335e9df91de7cdf763d27768c85c69e3)
- pending release [`4e5510e`](https://github.com/ImageMagick/ImageMagick6/commit/4e5510e020300678a4ea20a4e35348444981cba5)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=36990 [`9aa9170`](https://github.com/ImageMagick/ImageMagick6/commit/9aa91709d2b9ec1b98398e081e2fb67bb7e1718e)
- heap-based buffer overflow in TIFF coder (alert from Hunter Mitchell) [`35b88c9`](https://github.com/ImageMagick/ImageMagick6/commit/35b88c9166bc1b3ce8893f52217bae00d8e2c532)
- ... [`92a2023`](https://github.com/ImageMagick/ImageMagick6/commit/92a2023362cf5b2e31df3b9331015a3093deb65f)
- eliminate compiler warning [`1c9bcc6`](https://github.com/ImageMagick/ImageMagick6/commit/1c9bcc67803f7130afda8f2caa8bd8a5f1999dde)
- Whitespace [`4d1d0a6`](https://github.com/ImageMagick/ImageMagick6/commit/4d1d0a6a6adc8433126ec912c87336c797f92735)
- pending release [`0f1b20c`](https://github.com/ImageMagick/ImageMagick6/commit/0f1b20cf7eaa687847c1da3356961eb44e807911)
- pending release [`1e43b29`](https://github.com/ImageMagick/ImageMagick6/commit/1e43b291a5825520860b92acb3f7b52ba6145805)
- pending release [`d49be7f`](https://github.com/ImageMagick/ImageMagick6/commit/d49be7fbb7667ec214cd00a16145d7f4e3f1606e)
- pending release [`bf9a427`](https://github.com/ImageMagick/ImageMagick6/commit/bf9a4278c183d2713894d0ff1d4e97232cd2d70e)
- stop parsing after exception [`44c3bfc`](https://github.com/ImageMagick/ImageMagick6/commit/44c3bfc788dd4c94682093d480c514ab38543a2f)
- Use &amp; instead. [`8a23eb2`](https://github.com/ImageMagick/ImageMagick6/commit/8a23eb2603186c704f30d4b2f17bdefa5d6822d3)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`41c9434`](https://github.com/ImageMagick/ImageMagick6/commit/41c9434f427bcbba9163f4550cd034a6d8363fb9)
- https://github.com/ImageMagick/ImageMagick/issues/4059 [`54df923`](https://github.com/ImageMagick/ImageMagick6/commit/54df923634871204a7a371b9523ab63d67cc37d1)
- Only run the OpenCL benchmark when OpenCL is enabled. [`a04e6c4`](https://github.com/ImageMagick/ImageMagick6/commit/a04e6c49bdc19d9918d5a588ea3fd95f39dcd379)
- reduce memory moves [`0132164`](https://github.com/ImageMagick/ImageMagick6/commit/0132164f33ea82daf732f3923c2fb141cb834dcc)
- stop parsing on exception [`b915afb`](https://github.com/ImageMagick/ImageMagick6/commit/b915afb73148a8da5bca4a018a43c0432873d7fc)

## [6.9.12-19](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-18...6.9.12-19) - 2021-07-18

### Commits

- revert; keep CoreGenesis/CoreTerminus pairs; destroy wand ids [`2f3cc2c`](https://github.com/ImageMagick/ImageMagick6/commit/2f3cc2cf8339f1defd4215efcb320119de6ac1df)
- call MagickWandGenesis()/MagickWandTerminus() [`64aef14`](https://github.com/ImageMagick/ImageMagick6/commit/64aef14cc75b3bc0af31bc417060d79dfb6194e0)
- call wand genesis / terminus rather than core [`c4f26fb`](https://github.com/ImageMagick/ImageMagick6/commit/c4f26fbfd50bdb47397977758dc770f92b35a4bd)
- ... [`45df407`](https://github.com/ImageMagick/ImageMagick6/commit/45df407647856e7b5750767e49885b2f32a29c36)
- Fixed writing the iptc information when it is not stored as long. [`f4feb3e`](https://github.com/ImageMagick/ImageMagick6/commit/f4feb3eef7d1013f90babd21dee51736a21be1b2)
- install wand.h header that defines DestroyWandIDs() [`c2d788c`](https://github.com/ImageMagick/ImageMagick6/commit/c2d788c52ab9824c938af0a85ae83281d4c9c0a4)
- https://github.com/ImageMagick/ImageMagick/issues/3896 [`f939ee0`](https://github.com/ImageMagick/ImageMagick6/commit/f939ee00031464bd30cc69dcab8777f39ee8fbb8)
- ... [`3b491b8`](https://github.com/ImageMagick/ImageMagick6/commit/3b491b852a6f692ebc3ace6fee8ceb7ceb0adde9)
- pending release [`c0e73a4`](https://github.com/ImageMagick/ImageMagick6/commit/c0e73a46b330d6f58dd0f5bb5ecf7c9287812acb)
- pending release [`e28afaa`](https://github.com/ImageMagick/ImageMagick6/commit/e28afaa4eb6f184689c218debe9ba4874b9f727b)
- pending release [`1015767`](https://github.com/ImageMagick/ImageMagick6/commit/1015767a1429e3fa67b63853dc67d625171812c1)
- pending release [`5b9a9db`](https://github.com/ImageMagick/ImageMagick6/commit/5b9a9dbbe0c5b1654ff3185dee96fae0f0514295)
- https://github.com/ImageMagick/ImageMagick/issues/3951 [`e924a55`](https://github.com/ImageMagick/ImageMagick6/commit/e924a55afa85eff1780ad78d875f6429a50c4c11)
- ... [`d881b80`](https://github.com/ImageMagick/ImageMagick6/commit/d881b800c7f768bb5926e0ad730401bd866865cc)
- ... [`d09e86f`](https://github.com/ImageMagick/ImageMagick6/commit/d09e86f7d23784a2e8156ad7341a4221f0034d83)
- ... [`b847557`](https://github.com/ImageMagick/ImageMagick6/commit/b847557488c072763c2a0ecf62d0cfac5748353b)
- remove virtual canvas offset from similarity image [`1f974fd`](https://github.com/ImageMagick/ImageMagick6/commit/1f974fd9eb285da31989e97d51fca67648643ef2)

## [6.9.12-18](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-17...6.9.12-18) - 2021-07-17

### Merged

- uses the PerceptibleReciprocal() to prevent the divide-by-zero from occurring [`#3194`](https://github.com/ImageMagick/ImageMagick6/pull/3194)

### Commits

- Use the new issue templates. [`7c853af`](https://github.com/ImageMagick/ImageMagick6/commit/7c853afa3be12dfff22b34f0d2ddaf15180e66d9)
- optimize grayscale detection [`ec9feab`](https://github.com/ImageMagick/ImageMagick6/commit/ec9feabc987df9781c4e89f2ce014b75b02bfd0d)
- Corrected getting the image dimensions when identifying a postscript file. [`d624b59`](https://github.com/ImageMagick/ImageMagick6/commit/d624b590d2b1a4dd2d9f6794d6c388ca7b9069db)
- Fixed parsing the spot colors of a postscript document. [`ce84a88`](https://github.com/ImageMagick/ImageMagick6/commit/ce84a88592408d25533cd63a58ba7ee1b2b7c4cd)
- ... [`74f450e`](https://github.com/ImageMagick/ImageMagick6/commit/74f450e153dccb64bc254fca89318b00f6dd0eda)
- system() is not supported under IOS [`b9f3577`](https://github.com/ImageMagick/ImageMagick6/commit/b9f3577b509808187fcb9b4a8955d6327bcd0e09)
- The predictor tag should only be set for specific compression types. [`96c9b70`](https://github.com/ImageMagick/ImageMagick6/commit/96c9b7032d4b5cc3703cc32a1d59ab8c64a6a289)
- Added option to peek in the byte buffer. [`63bc851`](https://github.com/ImageMagick/ImageMagick6/commit/63bc85166df5b0c14562687252d8050cee1a73fb)
- Removed checklist. [`bc06359`](https://github.com/ImageMagick/ImageMagick6/commit/bc06359cf59e33b88ba0199f01ed4b5f1bbe8f6b)
- set imaginary component of the complex conjugate to -Ai [`f6b610f`](https://github.com/ImageMagick/ImageMagick6/commit/f6b610f6370b5140b86e50854a0b72dfc4d0dff0)
- check for zero demoninator [`e110b81`](https://github.com/ImageMagick/ImageMagick6/commit/e110b81fd38b2e15dc7495699de53df51f4ade91)
- Fixed copy paste mistake. [`0416173`](https://github.com/ImageMagick/ImageMagick6/commit/0416173677748e027ac772fa2094174a0a91b6d3)
- Added raqm to the autolinking list. [`756685f`](https://github.com/ImageMagick/ImageMagick6/commit/756685f4111943499a530c4bcf84b55964b8ba00)
- Make it more clear that no memory is leaking. [`7f0b16c`](https://github.com/ImageMagick/ImageMagick6/commit/7f0b16c0578766a578cdaa686e891b4812d17848)
- prevent blow up when standard deviation is 0 [`033df67`](https://github.com/ImageMagick/ImageMagick6/commit/033df67ae2d4ef2dc13952bfc48cbc5bef4b1686)
- pending release [`83e0280`](https://github.com/ImageMagick/ImageMagick6/commit/83e0280d488f14cf73f1e85cbf6857a56438f2db)
- proper cast [`4ce1321`](https://github.com/ImageMagick/ImageMagick6/commit/4ce1321c497e76e07d6c785840a2c6a0d2c6dbd8)
- https://github.com/ImageMagick/ImageMagick/issues/3925 [`cd274e4`](https://github.com/ImageMagick/ImageMagick6/commit/cd274e439e7bb49d18b1be7617d89f3be91b3188)

## [6.9.12-17](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-16...6.9.12-17) - 2021-06-25

### Commits

- ... [`801ffbd`](https://github.com/ImageMagick/ImageMagick6/commit/801ffbdc1a221e7a9947d22efb81101ce7fb2289)
- ... [`c1cb4d2`](https://github.com/ImageMagick/ImageMagick6/commit/c1cb4d26d533aa137cc5280aa6370f8d61150a1c)
- pending release [`fdb4ff6`](https://github.com/ImageMagick/ImageMagick6/commit/fdb4ff6575cb1012397a9a9e03f45924d56fd8fa)
- fix memory corruption in ConcatenateStringInfo [`7b5d5d9`](https://github.com/ImageMagick/ImageMagick6/commit/7b5d5d943fec12ccd167a6fed11758c609cb3275)
- ... [`8c99db4`](https://github.com/ImageMagick/ImageMagick6/commit/8c99db4d683f3fd1a4a89b85b3dc5c4b2c7295f4)

## [6.9.12-16](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-15...6.9.12-16) - 2021-06-20

### Commits

- ver allocate memory, typically used when concatentating strings [`73a59dc`](https://github.com/ImageMagick/ImageMagick6/commit/73a59dcd4eaae3a0cec565abda9c0dcb070c734a)
- ... [`dafa983`](https://github.com/ImageMagick/ImageMagick6/commit/dafa983fea7c9b0160c375435c53e83bc436b3c8)
- ... [`8aea6ca`](https://github.com/ImageMagick/ImageMagick6/commit/8aea6ca9f5363b4f5d6caaaa1df2c87a4bc43c82)
- https://github.com/ImageMagick/ImageMagick/issues/3844 [`fdf3836`](https://github.com/ImageMagick/ImageMagick6/commit/fdf38365635ec2e31d1c5294f1fb22a34917f2d4)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=35322 [`40f9bcd`](https://github.com/ImageMagick/ImageMagick6/commit/40f9bcd0f47d24eae4a9c3d542273af586938695)
- Revert patch that automatically changes the image orientation. [`086c8ee`](https://github.com/ImageMagick/ImageMagick6/commit/086c8eebf8df72086f2370b1e5c9ec72becaf89a)
- pending release [`46762e1`](https://github.com/ImageMagick/ImageMagick6/commit/46762e1b539aba1bfc7f39f6027a23a7cf84d276)
- pending release [`25aa96d`](https://github.com/ImageMagick/ImageMagick6/commit/25aa96dee935a052bd0b0893780bb5ea6bc4ecb4)
- Use the same typecast as in ImageMagick 7. [`d02e016`](https://github.com/ImageMagick/ImageMagick6/commit/d02e016daae2768e7abfc034c4b81d8fb3863617)
- pending release [`17d7b4b`](https://github.com/ImageMagick/ImageMagick6/commit/17d7b4bad2ca7fc7374164f1c40cb6f8282c4afb)
- ... [`d259da5`](https://github.com/ImageMagick/ImageMagick6/commit/d259da5de84df842780e79b5994a8d95b16c488c)

## [6.9.12-15](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-14...6.9.12-15) - 2021-06-12

### Commits

- Corrected writing the icc profile in a PDF file. [`5a73bdc`](https://github.com/ImageMagick/ImageMagick6/commit/5a73bdcc68d2b1a1a14df1324e0178778f7b9030)
- Write the number of channels of the color profile instead of the image (#2070). [`af88978`](https://github.com/ImageMagick/ImageMagick6/commit/af88978d2d35a047e1d7daa5a24df69e032db65a)
- https://github.com/ImageMagick/ImageMagick/issues/3786 [`ed858f9`](https://github.com/ImageMagick/ImageMagick6/commit/ed858f9af9797ddd07c818c0c84cfe1121d7fd9b)
- ... [`ece4978`](https://github.com/ImageMagick/ImageMagick6/commit/ece4978c35d73eee4eda064b8f429a6ad42a3bec)
- https://github.com/ImageMagick/ImageMagick/discussions/3813 [`dabbe44`](https://github.com/ImageMagick/ImageMagick6/commit/dabbe4450429779f526b9eb3ba29df9ff0653689)
- https://github.com/ImageMagick/ImageMagick/issues/3765 [`a8c277e`](https://github.com/ImageMagick/ImageMagick6/commit/a8c277e07d1a0c92179f830e9399ee7b8cc15931)
- Fixed memory leak when it failed to apply ICC color profile [`1d4b8f4`](https://github.com/ImageMagick/ImageMagick6/commit/1d4b8f499985f5b576b53b7b478a9c5ab82116d1)
- https://github.com/ImageMagick/ImageMagick/issues/3818 [`b21457a`](https://github.com/ImageMagick/ImageMagick6/commit/b21457a7eb9cb4c2f7c497b36a8efdab71beb4e6)
- ... [`637a850`](https://github.com/ImageMagick/ImageMagick6/commit/637a850cf7f3d87e35041b82ee6305503b996ea6)
- pending release [`15126f0`](https://github.com/ImageMagick/ImageMagick6/commit/15126f081300bac271947eb5dc21ecda6e85b070)
- When the compression is OJPEG the colorspace should not be changed to YCbCr. [`24fa0a8`](https://github.com/ImageMagick/ImageMagick6/commit/24fa0a82bdde4bec9d85ba9a59aebc5d83f17743)
- pending release [`f1893ff`](https://github.com/ImageMagick/ImageMagick6/commit/f1893ff113904f1062fbec74345e01fc708d0dba)
- https://github.com/ImageMagick/ImageMagick/issues/3818 [`4512ff0`](https://github.com/ImageMagick/ImageMagick6/commit/4512ff04e3bb51874129d4857734e235f52b974d)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=35024 [`cde1733`](https://github.com/ImageMagick/ImageMagick6/commit/cde173361e901f957e56640fe03f59e78d92168b)

## [6.9.12-14](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-12...6.9.12-14) - 2021-05-31

### Commits

- update copyright [`e65639e`](https://github.com/ImageMagick/ImageMagick6/commit/e65639eace3619b600881c0722a9f5f28b2d0f46)
- ... [`abd606b`](https://github.com/ImageMagick/ImageMagick6/commit/abd606b33eae106296b660e047adfc1e933ef900)
- ... [`14ea894`](https://github.com/ImageMagick/ImageMagick6/commit/14ea8946956a0b2be3c2c4acc73442ddfddee95a)
- https://github.com/ImageMagick/ImageMagick/issues/3687 [`274d848`](https://github.com/ImageMagick/ImageMagick6/commit/274d8481b11054b0c15c3b118e0fd2bb57919119)
- Removed travis build. [`bdff671`](https://github.com/ImageMagick/ImageMagick6/commit/bdff671dc524e5faae69fa9dfe53b6af7d7d6ffc)
- update CSS [`502d738`](https://github.com/ImageMagick/ImageMagick6/commit/502d73855661295eec94519ea83a1c31a1804d1a)
- Always use a wildcard in NTOpenDirectory. [`8305ee3`](https://github.com/ImageMagick/ImageMagick6/commit/8305ee3125b1d6cb9e6fb6978fae5a6ee6cb19f6)
- Added missing status checks. [`7b2c55c`](https://github.com/ImageMagick/ImageMagick6/commit/7b2c55c2280323956b7c70909775fc81cecf98bd)
- The path should not end in a backslash according to the MSDN documentation. [`8533847`](https://github.com/ImageMagick/ImageMagick6/commit/8533847ff7cfd9fb7de549d383179a65a7019ae9)
- ... [`e53f1fd`](https://github.com/ImageMagick/ImageMagick6/commit/e53f1fd02a97f521c4b26faf439b7b4bb55af58c)
- ... [`a792ea6`](https://github.com/ImageMagick/ImageMagick6/commit/a792ea62e0d72b86c2bb8502dec17f6e6d15c227)
- https://github.com/ImageMagick/ImageMagick/issues/3653 [`8e9b75e`](https://github.com/ImageMagick/ImageMagick6/commit/8e9b75ea13bf007724d5e6dd5625f9af7d6098fa)
- Fixed reading and writing the XMP chunk in a WebP image. [`62b736a`](https://github.com/ImageMagick/ImageMagick6/commit/62b736a9a6d7e736fabaaf728c8ecaaacadc2c7d)
- ... [`5e392ec`](https://github.com/ImageMagick/ImageMagick6/commit/5e392ec12363fdfd8fe9b5d98bbead89f560dd78)
- https://github.com/ImageMagick/ImageMagick/issues/3676 [`9d8e861`](https://github.com/ImageMagick/ImageMagick6/commit/9d8e86156f0f2c949623bfbd5c78d6c89a7c5467)
- https://github.com/ImageMagick/ImageMagick/pull/3749 [`6ba4b42`](https://github.com/ImageMagick/ImageMagick6/commit/6ba4b42dc9269f301952c1ec2dd0fb782834e00d)
- Removed unused variable. [`5b44db7`](https://github.com/ImageMagick/ImageMagick6/commit/5b44db70ca28b8f88ab5f9104570e85c4e16e74f)
- ... [`1b85287`](https://github.com/ImageMagick/ImageMagick6/commit/1b85287582cd72bcb128800d50878dd33a37ae65)
- Silence mingw warnings. [`a4ec89d`](https://github.com/ImageMagick/ImageMagick6/commit/a4ec89d233d6d5e03d558b14989322db7ec5f413)
- pending release [`6f1745f`](https://github.com/ImageMagick/ImageMagick6/commit/6f1745f5d593df4c3b98ec763c6b690abc1dec97)
- pending release [`f4efad9`](https://github.com/ImageMagick/ImageMagick6/commit/f4efad954ad505c71d17fa40f94af691d1492555)
- https://github.com/ImageMagick/ImageMagick/discussions/3583 [`d780ce0`](https://github.com/ImageMagick/ImageMagick6/commit/d780ce0a931d809e4452b7b3c8181806baeb1e8c)
- pending release [`7f8bf2f`](https://github.com/ImageMagick/ImageMagick6/commit/7f8bf2fe0325f577ab518fda227d068237065ac6)
- https://github.com/ImageMagick/ImageMagick/pull/3749 [`3233cab`](https://github.com/ImageMagick/ImageMagick6/commit/3233cab9b2a623626fe6d414b49dbe1a5b732a2d)
- NULL color name is acceptable [`d5a3cf7`](https://github.com/ImageMagick/ImageMagick6/commit/d5a3cf7270d1ef509ef61a55f51e33c1e894854b)
- The image type should not be changed when the image already has the correct type. [`8f74220`](https://github.com/ImageMagick/ImageMagick6/commit/8f74220f4f1dfdb0841f055402f19e219348af56)
- ... [`c75ae77`](https://github.com/ImageMagick/ImageMagick6/commit/c75ae771a00c38b757c5ef4b424b51e761b02552)
- eliminate heap buffer overflow vulnerability, thanks to ZhangJiaxing (@r0fm1a) from Codesafe Team of Legendsec at Qi'anxin Group [`b307bca`](https://github.com/ImageMagick/ImageMagick6/commit/b307bcadcdf6ea6819951ac1786b7904f27b25c6)
- https://github.com/ImageMagick/ImageMagick/issues/3690 [`2f1c004`](https://github.com/ImageMagick/ImageMagick6/commit/2f1c00490617ce067d8319866c8022411d17f2a4)
- pending release [`8947663`](https://github.com/ImageMagick/ImageMagick6/commit/89476634dafdafdf86573f75c6a34743d5805641)
- Moved definition of the define to this header file. [`5e2af4c`](https://github.com/ImageMagick/ImageMagick6/commit/5e2af4c542d0fee760eb9e2e0e3acd333156da0f)
- https://github.com/ImageMagick/ImageMagick/pull/3685/ [`2ac82aa`](https://github.com/ImageMagick/ImageMagick6/commit/2ac82aa7f502c779cbabd7f7c06d39eedcbfb042)

## [6.9.12-12](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-11...6.9.12-12) - 2021-05-09

### Commits

- improve exception testing [`94026fb`](https://github.com/ImageMagick/ImageMagick6/commit/94026fbfb045d27576799d84ee63320ba7cbc7aa)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`ed78be2`](https://github.com/ImageMagick/ImageMagick6/commit/ed78be2e62accb8ac0747fd2a72c9c52758b2f3a)
- support dither:diffusion-amount define for Riemersma dithering [`0d0f402`](https://github.com/ImageMagick/ImageMagick6/commit/0d0f402452dda40667926548882d18d2d336e141)
- ... [`5ec7ae6`](https://github.com/ImageMagick/ImageMagick6/commit/5ec7ae6d969667bb78d238649dd422e8f8441436)
- ... [`dd9b62d`](https://github.com/ImageMagick/ImageMagick6/commit/dd9b62d7ca80ffe5eebb34befc727ab3e59dc10b)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`8aa401e`](https://github.com/ImageMagick/ImageMagick6/commit/8aa401e00e229f0cb55ac733b9aa03c8bab884f5)
- pending release [`0d11539`](https://github.com/ImageMagick/ImageMagick6/commit/0d11539c266133971246eb2d0d49e626a43bcdf0)
- ... [`a5fec66`](https://github.com/ImageMagick/ImageMagick6/commit/a5fec668b59d0a725d96d56fae1b4864073f5b86)

## [6.9.12-11](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-10...6.9.12-11) - 2021-05-04

### Commits

- ... [`c46cd9f`](https://github.com/ImageMagick/ImageMagick6/commit/c46cd9fe551b567fb7b40bba052d3502d00f0f30)
- Replace tabs with spaces. [`b9d006e`](https://github.com/ImageMagick/ImageMagick6/commit/b9d006e0089fad6afab71528d34f00aa401e4023)
- Generate threshold-map.h instead. [`d4c3361`](https://github.com/ImageMagick/ImageMagick6/commit/d4c33614def7874b55607238f8fd83c8bbddea48)
- Add full threshold map [`c9753f9`](https://github.com/ImageMagick/ImageMagick6/commit/c9753f9113014a3d0283e8e4332447e7d1e5ed52)
- improve method name [`5d112e0`](https://github.com/ImageMagick/ImageMagick6/commit/5d112e0673ccc6f1632f6ff63c62d5a0bf6225e7)
- ... [`2316ca6`](https://github.com/ImageMagick/ImageMagick6/commit/2316ca67f6a6997b131aef292d33a1c38ee5cccf)
- ... [`3df3254`](https://github.com/ImageMagick/ImageMagick6/commit/3df32542e617b7df3291dded38a4825e926d8335)
- Use ExceptionInfo instead of letting libraw print to stderr. [`8462661`](https://github.com/ImageMagick/ImageMagick6/commit/8462661321389bab113b76bc74e0c27448914792)
- Corrected check in the TIFF decoder. [`a260de2`](https://github.com/ImageMagick/ImageMagick6/commit/a260de22e0676d0497ff780f0ccdbb795c05141b)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`caee165`](https://github.com/ImageMagick/ImageMagick6/commit/caee16574b1cce8f45cf01f63ea7a8988cbfe5fd)
- revert comments [`7d8a3b7`](https://github.com/ImageMagick/ImageMagick6/commit/7d8a3b762f3a9b1171d904da52293fe43cd8e0cb)
- pending release [`1ba0774`](https://github.com/ImageMagick/ImageMagick6/commit/1ba077420bd1a69c5dd5daed2c4a8736240ef256)
- ... [`e670f7f`](https://github.com/ImageMagick/ImageMagick6/commit/e670f7fc527eafe79134eb81786179f1760d9ec7)
- fix Makefile separator exception [`0d00ae7`](https://github.com/ImageMagick/ImageMagick6/commit/0d00ae7e3afb9e5022bb00ba042b5e5ee71c6bc3)
- https://github.com/ImageMagick/ImageMagick/issues/3468 [`5c22ac6`](https://github.com/ImageMagick/ImageMagick6/commit/5c22ac68a5077995db1ce40ddf37ea6ba14e3e29)
- Use magick instead of MagickCore. [`38f6779`](https://github.com/ImageMagick/ImageMagick6/commit/38f67793a6c37263e4aaffd8b9ef3c2510859836)
- Another attempt. [`816071e`](https://github.com/ImageMagick/ImageMagick6/commit/816071e70ea0dff2ec939dcb8a6b818f25e83d4f)
- fix names [`fbb8139`](https://github.com/ImageMagick/ImageMagick6/commit/fbb8139444e7d2debede07ceec91295243fb7619)
- cosmetic [`f944c0e`](https://github.com/ImageMagick/ImageMagick6/commit/f944c0efc98c5c6f7d6858666d6e3b207ad73e03)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33831 [`307f11e`](https://github.com/ImageMagick/ImageMagick6/commit/307f11e997b452a2a0a24abcf52eff16f4e11119)
- pending release [`930161d`](https://github.com/ImageMagick/ImageMagick6/commit/930161d603e2b65f363a10ba142e2ac732e28302)
- ... [`b3f69a1`](https://github.com/ImageMagick/ImageMagick6/commit/b3f69a17a508788164a973ed8b9f10264b776f8b)
- Corrected typo. [`3d0d0e0`](https://github.com/ImageMagick/ImageMagick6/commit/3d0d0e0564339cf93da53852fa50005b55890e87)

## [6.9.12-10](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-9...6.9.12-10) - 2021-04-28

### Merged

- Fix line endings in Geometry.h to LF. [`#149`](https://github.com/ImageMagick/ImageMagick6/pull/149)
- Fix incorrect client_data pointer being set in libjpeg context. [`#152`](https://github.com/ImageMagick/ImageMagick6/pull/152)

### Fixed

- Fix incorrect client_data pointer being set in libjpeg context. (#152) [`#150`](https://github.com/ImageMagick/ImageMagick6/issues/150) [`#151`](https://github.com/ImageMagick/ImageMagick6/issues/151)

### Commits

- ... [`c770f50`](https://github.com/ImageMagick/ImageMagick6/commit/c770f508dea2e72791845e745696092f3e794a58)
- check image is not NULL before dereferencing [`5ee7e3e`](https://github.com/ImageMagick/ImageMagick6/commit/5ee7e3eae5a0f4c06969c5b99a0a605901c0eac1)
- ... [`99cbc9f`](https://github.com/ImageMagick/ImageMagick6/commit/99cbc9f2542b9857c8abe580870b2b7a59e60731)
- pending release [`fea001e`](https://github.com/ImageMagick/ImageMagick6/commit/fea001e31a471c1e6605aa6e6ae97fb554a0e784)
- pending release [`370ce4c`](https://github.com/ImageMagick/ImageMagick6/commit/370ce4c7e2f6c04a672ca0b5ebb05acb490e31e9)

## [6.9.12-9](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-8...6.9.12-9) - 2021-04-24

### Commits

- cosmetic [`3832fa1`](https://github.com/ImageMagick/ImageMagick6/commit/3832fa11c51785a611e7a7cc9c57073221ed7833)
- ... [`878f631`](https://github.com/ImageMagick/ImageMagick6/commit/878f6315caa7d8b9f0c616147e71a2f2b25b1756)
- cosmetic [`47e1eab`](https://github.com/ImageMagick/ImageMagick6/commit/47e1eabbc7736a08aed1ec225a07357f65d19ede)
- ... [`99b82fe`](https://github.com/ImageMagick/ImageMagick6/commit/99b82feded146a666b808c977db248c0e78bc757)
- https://github.com/ImageMagick/ImageMagick/issues/3571 [`68a0f3f`](https://github.com/ImageMagick/ImageMagick6/commit/68a0f3f8b8e90190c78bc65403fc81192fb3da59)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33466 [`6cf7fd8`](https://github.com/ImageMagick/ImageMagick6/commit/6cf7fd8e84aedcdfb125120b230f5a1dcf781169)
- ... [`181125f`](https://github.com/ImageMagick/ImageMagick6/commit/181125f67ecf9ac57adef1db861181d8d6adbe70)
- ... [`969b02d`](https://github.com/ImageMagick/ImageMagick6/commit/969b02d7a66e0d74a5290183e334995586e4a3dd)
- Corrected ChangeLog. [`165f89f`](https://github.com/ImageMagick/ImageMagick6/commit/165f89f5c3cdd05a49c08c001187c8ccfb5d6e58)
- pending release [`e9740ab`](https://github.com/ImageMagick/ImageMagick6/commit/e9740ab2ea9ce835003966551ceebcae4ce16ff1)
- Corrected typo. [`c8c3cf8`](https://github.com/ImageMagick/ImageMagick6/commit/c8c3cf8a1d7f93de7127606e5ccc0f2068216322)
- ... [`fb64736`](https://github.com/ImageMagick/ImageMagick6/commit/fb647360465898972581c5a44d92f05040c61bbf)
- ... [`6fd9c48`](https://github.com/ImageMagick/ImageMagick6/commit/6fd9c48d18522fc739988c635b4f230f5a9553a9)

## [6.9.12-8](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-7...6.9.12-8) - 2021-04-17

### Commits

- latest automake/autoconf [`1fb5916`](https://github.com/ImageMagick/ImageMagick6/commit/1fb5916a9010c993a6e77613310828e950c8959f)
- ... [`24030ed`](https://github.com/ImageMagick/ImageMagick6/commit/24030ed4a3009bac808989e4142942074308bd33)
- https://github.com/ImageMagick/ImageMagick/issues/3549 [`0962d40`](https://github.com/ImageMagick/ImageMagick6/commit/0962d402b0af0d31d7267bb82f5460c53c54518e)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33350 [`0eccd35`](https://github.com/ImageMagick/ImageMagick6/commit/0eccd3556a8c456239a49f9064381ddc3e28476e)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`0fcebd3`](https://github.com/ImageMagick/ImageMagick6/commit/0fcebd3e7a382830a8e56b98b3f67e06b4beadb3)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33232 [`e699f55`](https://github.com/ImageMagick/ImageMagick6/commit/e699f559dfa912cf979893ab2cde9a0695218c30)
- https://github.com/ImageMagick/ImageMagick/issues/3540 [`cd7f9fb`](https://github.com/ImageMagick/ImageMagick6/commit/cd7f9fb7751b0d59d5a74b12d971155caad5a792)
- pending release [`e65db11`](https://github.com/ImageMagick/ImageMagick6/commit/e65db11090a270d7200adac080f623a7e75b1e96)
- pending release [`e06e7ff`](https://github.com/ImageMagick/ImageMagick6/commit/e06e7ffbf1fa16039754558eac75a917bd827393)
- https://github.com/ImageMagick/ImageMagick/issues/3537 [`5b0acdb`](https://github.com/ImageMagick/ImageMagick6/commit/5b0acdb5047fd322ea9ba3cbf7fe0718e3cda0af)
- write tiff colormapped images with an alpha channel as PHOTOMETRIC_RGB [`270494f`](https://github.com/ImageMagick/ImageMagick6/commit/270494f4ba392f230b2e816667416e5ac638e275)

## [6.9.12-7](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-6...6.9.12-7) - 2021-04-11

### Merged

- fix perl syntax [`#144`](https://github.com/ImageMagick/ImageMagick6/pull/144)

### Commits

- ... [`b9a79ba`](https://github.com/ImageMagick/ImageMagick6/commit/b9a79ba19226ea0d5f81b61bb06b4b84f1bb7bcd)
- add a nonce to the signature generation [`d9600ec`](https://github.com/ImageMagick/ImageMagick6/commit/d9600ec25644b74d8be1bd432f280b2467c5e175)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=33137 [`d94de13`](https://github.com/ImageMagick/ImageMagick6/commit/d94de132dce98a02dce3451dfc014d2286fa0d43)
- constrain sub-image list [`c4392ae`](https://github.com/ImageMagick/ImageMagick6/commit/c4392aee303fba6d5e813f8c2ae1b67c19b438cb)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`bec4e2d`](https://github.com/ImageMagick/ImageMagick6/commit/bec4e2dabf96dd93ef0ca7bb384521acdcb4be1e)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`d4f04b4`](https://github.com/ImageMagick/ImageMagick6/commit/d4f04b4dfb783996b8f48c28d64c04ca8b8cd542)
- revert patch [`3415a1d`](https://github.com/ImageMagick/ImageMagick6/commit/3415a1db1c4dfd8dc096f45c80f647e047da0cd8)
- pending release [`e183af8`](https://github.com/ImageMagick/ImageMagick6/commit/e183af8ec3d8ce2d36e55beda63535052ff429ed)
- ... [`e3ad231`](https://github.com/ImageMagick/ImageMagick6/commit/e3ad2313517d78a96b5bcfce1cd4ce37c9df8dba)
- https://github.com/ImageMagick/ImageMagick6/security/code-scanning/5?query=ref%3Arefs%2Fheads%2Fmain [`822e476`](https://github.com/ImageMagick/ImageMagick6/commit/822e4768034198ff0bcc41b551462295ca5baec6)
- https://github.com/ImageMagick/ImageMagick6/issues/145 [`bc7f4f5`](https://github.com/ImageMagick/ImageMagick6/commit/bc7f4f54206f2053a45959e07704c7fc657e07aa)
- ... [`0dbacf8`](https://github.com/ImageMagick/ImageMagick6/commit/0dbacf8c67e2788f3d13b6d9b442b72bfad2d055)
- pending release [`a14972b`](https://github.com/ImageMagick/ImageMagick6/commit/a14972b0323163a8a41e4e34213da2b277bce372)
- pending release [`8608fb1`](https://github.com/ImageMagick/ImageMagick6/commit/8608fb14228480364cda4080c1b2d3ed118d8b8d)
- https://github.com/ImageMagick/ImageMagick/issues/3520 [`4c0a1d5`](https://github.com/ImageMagick/ImageMagick6/commit/4c0a1d5b7a230b84e2d420c592ce7bc355ebd785)
- pending release [`b37dd2c`](https://github.com/ImageMagick/ImageMagick6/commit/b37dd2c732634c98c0beef253f3e03216cdb3fc0)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`75c05e1`](https://github.com/ImageMagick/ImageMagick6/commit/75c05e1a2b1763712a6d9ca9de237c0d9198647e)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`89f9691`](https://github.com/ImageMagick/ImageMagick6/commit/89f9691ab4fdfbb8cacbe6718a0e3b911982b0ff)

## [6.9.12-6](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-5...6.9.12-6) - 2021-04-03

### Commits

- ... [`312df44`](https://github.com/ImageMagick/ImageMagick6/commit/312df44858c91c2b43c07f7bd7b61cea7332d31f)
- revert patch [`7703d3b`](https://github.com/ImageMagick/ImageMagick6/commit/7703d3b2c13e56cc7fe7ca004228e4e2d9b8067f)
- prevent undefined-behavior issue reported by Hardik [`798838f`](https://github.com/ImageMagick/ImageMagick6/commit/798838f31c0112c10491bf2cf2a4d084be90e26f)
- ... [`f2a5d86`](https://github.com/ImageMagick/ImageMagick6/commit/f2a5d8646472e4bc5cd0a18546db0a29d3b7795c)
- pending release [`328bd1a`](https://github.com/ImageMagick/ImageMagick6/commit/328bd1a082a497239938910b4bff8b9bcc2cf768)
- ... [`6c4bc78`](https://github.com/ImageMagick/ImageMagick6/commit/6c4bc786e900ef6ac08483d1cbe963ed3210eddf)
- pending release [`0f40ca2`](https://github.com/ImageMagick/ImageMagick6/commit/0f40ca207b30abfdd9e7c8868e6005c137c032b7)
- https://github.com/ImageMagick/ImageMagick/security/code-scanning/30 [`cbc076e`](https://github.com/ImageMagick/ImageMagick6/commit/cbc076e95697faed2cfb1abcd60693b859135330)
- Added missing null check. [`3f8f861`](https://github.com/ImageMagick/ImageMagick6/commit/3f8f8611b5cc7ba945eacc17ad801840b423c2c6)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`fbecaf0`](https://github.com/ImageMagick/ImageMagick6/commit/fbecaf01e52c45465d2cfad8272bc578e469c953)
- pending release [`fd23993`](https://github.com/ImageMagick/ImageMagick6/commit/fd23993f35fbfb48353bdcf16da1767f13eb4e71)
- pending release [`7aab092`](https://github.com/ImageMagick/ImageMagick6/commit/7aab092ac4e77ec6d96fcfe74c53eaf3e6cf159d)
- pending release [`0e74340`](https://github.com/ImageMagick/ImageMagick6/commit/0e74340c0adaa4370e971079c654fe405b57e607)
- https://github.com/ImageMagick/ImageMagick/issues/3469 [`f8e4322`](https://github.com/ImageMagick/ImageMagick6/commit/f8e4322d169b0db00ca438c68bed0f4b5c5cabb5)

## [6.9.12-5](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-4...6.9.12-5) - 2021-03-28

### Commits

- https://github.com/ImageMagick/ImageMagick/issues/3428 [`4f47d5f`](https://github.com/ImageMagick/ImageMagick6/commit/4f47d5f43e7a776cb615433867945f86a556ae51)
- ... [`9a4bc34`](https://github.com/ImageMagick/ImageMagick6/commit/9a4bc34b4b985e7cf604dc58691e64c576d8c3bd)
- eliminate C++ compile exception [`adda0fe`](https://github.com/ImageMagick/ImageMagick6/commit/adda0fe816d5098691aeec1b690d5178d4fe2a17)
- fix handling of non-square images with -fft option [`ffa0d49`](https://github.com/ImageMagick/ImageMagick6/commit/ffa0d49a7556be8f5e9ebf9c14096e5a6102bff8)
- Disable OpenCL by default. [`9a5b074`](https://github.com/ImageMagick/ImageMagick6/commit/9a5b07493a639c063caaac334b2e664c2484df7d)
- latest beta release [`4981820`](https://github.com/ImageMagick/ImageMagick6/commit/498182048b243c1a20891edb69545832c8d17d80)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=32322 [`c8f2595`](https://github.com/ImageMagick/ImageMagick6/commit/c8f25953ad1dd38a8b2d92738f0f742ad7e0bce7)
- ... [`3e34aa8`](https://github.com/ImageMagick/ImageMagick6/commit/3e34aa8bdf295e0a9d1630eab6c45cbdc2d90d4f)
- pending release [`8dc8e09`](https://github.com/ImageMagick/ImageMagick6/commit/8dc8e090e29c15161de42b62935b706a11e53477)
- eliminate compiler warning [`6a5d357`](https://github.com/ImageMagick/ImageMagick6/commit/6a5d3575487487f2703383338bd17c8c25068f19)
- Throw exception when no exception was raised but status was false (#3432). [`512668d`](https://github.com/ImageMagick/ImageMagick6/commit/512668dfd92b20d0d08b91d62b422d8262573281)
- fix c++ compiler exception [`0ec46fc`](https://github.com/ImageMagick/ImageMagick6/commit/0ec46fc805a5e7a4056b9614c7a994bfb39e53b0)
- pending release [`0be2e6a`](https://github.com/ImageMagick/ImageMagick6/commit/0be2e6a5063613c1ed795a863916ccc4481514ce)

## [6.9.12-4](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-3...6.9.12-4) - 2021-03-20

### Commits

- ... [`8a98e9f`](https://github.com/ImageMagick/ImageMagick6/commit/8a98e9ff9ee7455551aff6981b5d8503c507bfbc)
- ... [`b7ed95d`](https://github.com/ImageMagick/ImageMagick6/commit/b7ed95d47f9a22fac2ab45769d7144fa988429ed)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=31872 [`2a56e44`](https://github.com/ImageMagick/ImageMagick6/commit/2a56e447a4a60a4b89fc8be0410a6db39d5e3de3)
- ... [`b13e1a8`](https://github.com/ImageMagick/ImageMagick6/commit/b13e1a86fdfc92aa7aa04bedbfa2e43f8c216667)
- ... [`06d7298`](https://github.com/ImageMagick/ImageMagick6/commit/06d729858570caa124a24887cf723fe9679881d4)
- pending release [`9b40562`](https://github.com/ImageMagick/ImageMagick6/commit/9b405621909fa2e67170178f795a115ddbe9e1db)
- ... [`fa69ed6`](https://github.com/ImageMagick/ImageMagick6/commit/fa69ed6f43ca120d9dfb5570330602de6badcf90)
- pending release [`4ef5c73`](https://github.com/ImageMagick/ImageMagick6/commit/4ef5c73c83203e93b60a092e3bc74697a3310c7f)
- ... [`21991f7`](https://github.com/ImageMagick/ImageMagick6/commit/21991f726e6a7505bf14f593033cc75533c8b783)
- avoid omp deadlock [`99ac197`](https://github.com/ImageMagick/ImageMagick6/commit/99ac1977da0883b78cd4e9b763f267e8bce389e8)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=28891 [`f940ecb`](https://github.com/ImageMagick/ImageMagick6/commit/f940ecb921b7ab83da320334349f0cde1ff7f3e6)
- ... [`2204eb5`](https://github.com/ImageMagick/ImageMagick6/commit/2204eb57ae00b005b39165a47b8984eac01600a5)
- https://github.com/ImageMagick/ImageMagick/discussions/3389 [`df6b526`](https://github.com/ImageMagick/ImageMagick6/commit/df6b5268be37616ab479b833fa78951a3bd4e8a1)
- ... [`6d5f5d8`](https://github.com/ImageMagick/ImageMagick6/commit/6d5f5d8892fa316aad710521792d23fc7c783734)

## [6.9.12-3](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-2...6.9.12-3) - 2021-03-06

### Commits

- ... [`0370b8e`](https://github.com/ImageMagick/ImageMagick6/commit/0370b8e16fd3d7900005040d1663d676268ab1b3)
- https://github.com/ImageMagick/ImageMagick/issues/3332 [`072d7b1`](https://github.com/ImageMagick/ImageMagick6/commit/072d7b10dbe74d1cf4ec0d008990c1a28c076f9e)
- https://github.com/ImageMagick/ImageMagick/issues/3334 [`1b3585f`](https://github.com/ImageMagick/ImageMagick6/commit/1b3585fb7adb4ced6609d58ce9c9feb43dffeaaf)
- ... [`c51b249`](https://github.com/ImageMagick/ImageMagick6/commit/c51b2495fcfddc4b77908e2034ca1877c3b4a8bf)
- pending release [`4a83315`](https://github.com/ImageMagick/ImageMagick6/commit/4a833158dd16e127e3ca042baed6b449630ec5e2)
- https://github.com/ImageMagick/ImageMagick/issues/3340 [`448f927`](https://github.com/ImageMagick/ImageMagick6/commit/448f9271ef479569fc46583b9aa4ddc5c962d867)
- https://github.com/ImageMagick/ImageMagick/issues/3331 [`4eafab8`](https://github.com/ImageMagick/ImageMagick6/commit/4eafab89a2742865d770857a9d7434993f65ae6b)
- slight adjustment to D65 illuminant [`1df11cf`](https://github.com/ImageMagick/ImageMagick6/commit/1df11cf4efb748e55d7366f46c6e3a847a742487)
- ... [`aa77b65`](https://github.com/ImageMagick/ImageMagick6/commit/aa77b657b123bf92843f96c610b85e1a389e8226)
- https://github.com/ImageMagick/ImageMagick/issues/3333 [`366c970`](https://github.com/ImageMagick/ImageMagick6/commit/366c9708a7ca1256ee03d0d4addb2690ed42273f)
- https://github.com/ImageMagick/ImageMagick/issues/3337 [`4bf64fd`](https://github.com/ImageMagick/ImageMagick6/commit/4bf64fdd786728f372e8a701a663caa2774e7a23)
- ... [`522b4a3`](https://github.com/ImageMagick/ImageMagick6/commit/522b4a3e5bd272873cdc81aa5fdffdc4c520d588)
- https://github.com/ImageMagick/ImageMagick/issues/3336 [`5d33b8d`](https://github.com/ImageMagick/ImageMagick6/commit/5d33b8df73b0b1e40ee3fb7a334d28d929ae903c)
- https://github.com/ImageMagick/ImageMagick/issues/3335 [`ad492c7`](https://github.com/ImageMagick/ImageMagick6/commit/ad492c7ed4cf1cf285a7f6e2ee5a1e7cf24e73b2)
- https://github.com/ImageMagick/ImageMagick/issues/3339 [`9a94877`](https://github.com/ImageMagick/ImageMagick6/commit/9a94877f7823b0b8a41d50638dd105229d91fa89)
- https://github.com/ImageMagick/ImageMagick/issues/3338 [`4b5e026`](https://github.com/ImageMagick/ImageMagick6/commit/4b5e026c704d777efe9c2ead5dd68ca4fe3b2aa1)
- ... [`c498edc`](https://github.com/ImageMagick/ImageMagick6/commit/c498edcef55dea47d6c3c4f2636c467343299ec2)

## [6.9.12-2](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-1...6.9.12-2) - 2021-02-27

### Commits

- ... [`c8d0040`](https://github.com/ImageMagick/ImageMagick6/commit/c8d0040f8505ee16266dd57b3abda80d7f19fead)
- possible divide by zero + clear buffers [`e53e24b`](https://github.com/ImageMagick/ImageMagick6/commit/e53e24b078f7fa586f9cc910491b8910f5bdad2e)
- ... [`d945f43`](https://github.com/ImageMagick/ImageMagick6/commit/d945f43d0a103ec4af50816aab54ab3d3b574543)
- check that image exists before we destroy it [`3418473`](https://github.com/ImageMagick/ImageMagick6/commit/34184739956fd739735d364ec5b15c2ee89568cf)
- https://github.com/ImageMagick/ImageMagick/issues/3317 [`bbb2dff`](https://github.com/ImageMagick/ImageMagick6/commit/bbb2dff98d0e97a0fe3f7e187855476c4590eed2)
- https://github.com/ImageMagick/ImageMagick/issues/3297 [`841138c`](https://github.com/ImageMagick/ImageMagick6/commit/841138cc282722a80e06977d683405a0cf1d78ef)
- cosmetic [`63d4768`](https://github.com/ImageMagick/ImageMagick6/commit/63d47686efceeeb4ee68daa01614aab76eecf07c)
- https://github.com/ImageMagick/ImageMagick/issues/3321 [`64c0cc2`](https://github.com/ImageMagick/ImageMagick6/commit/64c0cc234280544dabacc2b28017521851deebde)
- pending release [`309cf43`](https://github.com/ImageMagick/ImageMagick6/commit/309cf4397c0d3d9963af04aa9a56fe406446c656)
- pending release [`a9c2639`](https://github.com/ImageMagick/ImageMagick6/commit/a9c26392e18cf38d50621ab1719539cb7bf79a61)
- fix compiler exception [`2e0bf51`](https://github.com/ImageMagick/ImageMagick6/commit/2e0bf51d81f5b9e5669699ace345330270991d00)
- pending release [`627cbd7`](https://github.com/ImageMagick/ImageMagick6/commit/627cbd7ea1e15ea2c9c0b7789e71b4e3a4aba962)
- pending release [`588d323`](https://github.com/ImageMagick/ImageMagick6/commit/588d3230ca82c14f2de6e1e894311d9d4fcdb05d)
- pending release [`eb69a8a`](https://github.com/ImageMagick/ImageMagick6/commit/eb69a8adc86a9b6a43d81f39b20a33f6a74d0013)
- https://github.com/ImageMagick/ImageMagick/issues/3320 [`b365302`](https://github.com/ImageMagick/ImageMagick6/commit/b3653027e9dc93d03917db602b83d15e70fee575)
- pending release [`abad074`](https://github.com/ImageMagick/ImageMagick6/commit/abad074de78b7a71afe8785b046885e0d16d75ce)
- https://github.com/ImageMagick/ImageMagick/issues/3296 [`f1e68d2`](https://github.com/ImageMagick/ImageMagick6/commit/f1e68d22d1b35459421710587a0dcbab6900b51f)
- pending release [`c5e7a8b`](https://github.com/ImageMagick/ImageMagick6/commit/c5e7a8bbe66dd101d81f2bb16be232bfdb2d6d45)
- pending release [`7d56434`](https://github.com/ImageMagick/ImageMagick6/commit/7d564341fe48bcab733188573e0e7d41674ad80c)
- ... [`4c08b0d`](https://github.com/ImageMagick/ImageMagick6/commit/4c08b0d598c753b5e0e5cc99be5c47c62323c6e0)

## [6.9.12-1](https://github.com/ImageMagick/ImageMagick6/compare/6.9.12-0...6.9.12-1) - 2021-02-21

### Commits

- ... [`ea03af8`](https://github.com/ImageMagick/ImageMagick6/commit/ea03af8be5183f7a2fda2afad06e4e9a0a75893b)
- ... [`7854805`](https://github.com/ImageMagick/ImageMagick6/commit/7854805a0e012213dad5b813e0de78799348f255)
- ... [`268dc9f`](https://github.com/ImageMagick/ImageMagick6/commit/268dc9f87749044cc2de2e384128e6a4aed06669)
- https://github.com/ImageMagick/ImageMagick/issues/3258 [`d285259`](https://github.com/ImageMagick/ImageMagick6/commit/d2852597c575cad62a65ed6edeeb8f5a36077add)
- ... [`f27cfb1`](https://github.com/ImageMagick/ImageMagick6/commit/f27cfb112338057f8fac5d6b016b3c69fb119b84)
- pending release [`05fc76c`](https://github.com/ImageMagick/ImageMagick6/commit/05fc76c3de140ab0ee5438b6be2d52bd5d8c323a)
- https://github.com/ImageMagick/ImageMagick/issues/3259 [`e6a300e`](https://github.com/ImageMagick/ImageMagick6/commit/e6a300ef2da27bcf767fdc9f43aea9bb73054b33)
- https://github.com/ImageMagick/ImageMagick/pull/3241 [`a19d95d`](https://github.com/ImageMagick/ImageMagick6/commit/a19d95d36f92b4266364fa6bbcea3e2cc0da712d)
- https://github.com/ImageMagick/ImageMagick/issues/3242 [`68ce241`](https://github.com/ImageMagick/ImageMagick6/commit/68ce2418726f566e43624f2ef1906d86746c8c2e)
- ... [`90510e0`](https://github.com/ImageMagick/ImageMagick6/commit/90510e0d208d498650ff6400fd405bdf1711e082)

## [6.9.12-0](https://github.com/ImageMagick/ImageMagick6/compare/6.9.11-62...6.9.12-0) - 2021-02-13

### Commits

- update docs [`dab48ba`](https://github.com/ImageMagick/ImageMagick6/commit/dab48bafd2924a7349df9bdc1ce8c36fab893bc2)
- bump minor release [`9f1d23f`](https://github.com/ImageMagick/ImageMagick6/commit/9f1d23fa325165a3426ba401b552e65397384e96)
- ... [`5d2e553`](https://github.com/ImageMagick/ImageMagick6/commit/5d2e553ff197322676b36c32da7079d2f6e41633)
- ... [`efb5ce8`](https://github.com/ImageMagick/ImageMagick6/commit/efb5ce8710604e7b86014a70e91d0372a3930b5b)
- ... [`d886aa5`](https://github.com/ImageMagick/ImageMagick6/commit/d886aa509b6258e5312d28d4c106803491f31d92)
- ... [`0824c17`](https://github.com/ImageMagick/ImageMagick6/commit/0824c17ef4405641322bab4c9d717a30b6c80162)
- ... [`dfd1d7f`](https://github.com/ImageMagick/ImageMagick6/commit/dfd1d7f43c68c4449a1e8666ea6087ff4ff17a05)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=30839 [`6f604e9`](https://github.com/ImageMagick/ImageMagick6/commit/6f604e9cc06ea1291b6932fa7786c3a01306c424)
- cosmetic [`c8922ae`](https://github.com/ImageMagick/ImageMagick6/commit/c8922ae40e995f93654eeeeb90266867e4a00154)
- ... [`37d7edf`](https://github.com/ImageMagick/ImageMagick6/commit/37d7edfc6b4f7270a9539c14541a7d1d7358b6f2)
- pending release [`769536d`](https://github.com/ImageMagick/ImageMagick6/commit/769536d06c3dc2171aac1ddd36a01edfa16b1977)
- https://bugs.chromium.org/p/oss-fuzz/issues/detail?id=30896 [`b322ab0`](https://github.com/ImageMagick/ImageMagick6/commit/b322ab0074a86cc62073a2b577ef21907f3111d7)
