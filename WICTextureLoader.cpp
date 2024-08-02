#include <wincodec.h>
#include "ImageUtils.h"
#include "RendererCommon.h"
#include "RefCountPtr.h"

constexpr auto FORMAT_MAPPINGS_SIZE = 17;
constexpr auto FORMAT_CONVERSIONS_SIZE = 41;

struct PixelFormatMapping
{
	WICPixelFormatGUID wicPixelFormat;
	DXGI_FORMAT dxgiFormat;
};

PixelFormatMapping formatMappings[FORMAT_MAPPINGS_SIZE] =
{
	{ GUID_WICPixelFormat128bppRGBAFloat, DXGI_FORMAT_R32G32B32A32_FLOAT },
	{ GUID_WICPixelFormat64bppRGBAHalf, DXGI_FORMAT_R16G16B16A16_FLOAT },
	{ GUID_WICPixelFormat64bppRGBA, DXGI_FORMAT_R16G16B16A16_UNORM },
	{ GUID_WICPixelFormat32bppRGBA, DXGI_FORMAT_R8G8B8A8_UNORM },
	{ GUID_WICPixelFormat32bppBGRA, DXGI_FORMAT_B8G8R8A8_UNORM },
	{ GUID_WICPixelFormat32bppBGR, DXGI_FORMAT_B8G8R8X8_UNORM },
	{ GUID_WICPixelFormat32bppRGBA1010102XR, DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM },
	{ GUID_WICPixelFormat32bppRGBA1010102, DXGI_FORMAT_R10G10B10A2_UNORM },
	{ GUID_WICPixelFormat32bppRGBE, DXGI_FORMAT_R9G9B9E5_SHAREDEXP },
	{ GUID_WICPixelFormat16bppBGRA5551, DXGI_FORMAT_B5G5R5A1_UNORM },
	{ GUID_WICPixelFormat16bppBGR565, DXGI_FORMAT_B5G6R5_UNORM },
	{ GUID_WICPixelFormat32bppGrayFloat, DXGI_FORMAT_R32_FLOAT },
	{ GUID_WICPixelFormat16bppGrayHalf, DXGI_FORMAT_R16_FLOAT },
	{ GUID_WICPixelFormat16bppGray, DXGI_FORMAT_R16_UNORM },
	{ GUID_WICPixelFormat8bppGray, DXGI_FORMAT_R8_UNORM },
	{ GUID_WICPixelFormat8bppAlpha, DXGI_FORMAT_A8_UNORM },
	{ GUID_WICPixelFormat96bppRGBFloat, DXGI_FORMAT_R32G32B32_FLOAT }
};

struct PixelFormatConversion
{
	WICPixelFormatGUID sourceFormat;
	WICPixelFormatGUID targetFormat;
};

PixelFormatConversion formatConversions[] =
{
	{ GUID_WICPixelFormatBlackWhite, GUID_WICPixelFormat8bppGray },

	{ GUID_WICPixelFormat1bppIndexed, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat2bppIndexed, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat4bppIndexed, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat8bppIndexed, GUID_WICPixelFormat32bppRGBA },

	{ GUID_WICPixelFormat2bppGray, GUID_WICPixelFormat8bppGray },
	{ GUID_WICPixelFormat4bppGray, GUID_WICPixelFormat8bppGray },

	{ GUID_WICPixelFormat16bppGrayFixedPoint, GUID_WICPixelFormat16bppGrayHalf },
	{ GUID_WICPixelFormat32bppGrayFixedPoint, GUID_WICPixelFormat32bppGrayFloat },

#ifdef DXGI_1_2_FORMATS

	{ GUID_WICPixelFormat16bppBGR555, GUID_WICPixelFormat16bppBGRA5551 },

#else

	{ GUID_WICPixelFormat16bppBGR555, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat16bppBGRA5551, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat16bppBGR565, GUID_WICPixelFormat32bppRGBA },

#endif

	{ GUID_WICPixelFormat32bppBGR101010, GUID_WICPixelFormat32bppRGBA1010102 },

	{ GUID_WICPixelFormat24bppBGR, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat24bppRGB, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat32bppPBGRA, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat32bppPRGBA, GUID_WICPixelFormat32bppRGBA },

	{ GUID_WICPixelFormat48bppRGB, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat48bppBGR, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat64bppBGRA, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat64bppPRGBA, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat64bppPBGRA, GUID_WICPixelFormat64bppRGBA },

	{ GUID_WICPixelFormat48bppRGBFixedPoint, GUID_WICPixelFormat64bppRGBAHalf },
	{ GUID_WICPixelFormat48bppBGRFixedPoint, GUID_WICPixelFormat64bppRGBAHalf },
	{ GUID_WICPixelFormat64bppRGBAFixedPoint, GUID_WICPixelFormat64bppRGBAHalf },
	{ GUID_WICPixelFormat64bppBGRAFixedPoint, GUID_WICPixelFormat64bppRGBAHalf },
	{ GUID_WICPixelFormat64bppRGBFixedPoint,  GUID_WICPixelFormat64bppRGBAHalf },
	{ GUID_WICPixelFormat64bppRGBHalf, GUID_WICPixelFormat64bppRGBAHalf },
	{ GUID_WICPixelFormat48bppRGBHalf, GUID_WICPixelFormat64bppRGBAHalf },

	{ GUID_WICPixelFormat96bppRGBFixedPoint, GUID_WICPixelFormat128bppRGBAFloat }, 
	{ GUID_WICPixelFormat128bppPRGBAFloat, GUID_WICPixelFormat128bppRGBAFloat }, 
	{ GUID_WICPixelFormat128bppRGBFloat, GUID_WICPixelFormat128bppRGBAFloat },
	{ GUID_WICPixelFormat128bppRGBAFixedPoint, GUID_WICPixelFormat128bppRGBAFloat },
	{ GUID_WICPixelFormat128bppRGBFixedPoint, GUID_WICPixelFormat128bppRGBAFloat },

	{ GUID_WICPixelFormat32bppCMYK, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat64bppCMYK, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat40bppCMYKAlpha, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat80bppCMYKAlpha, GUID_WICPixelFormat64bppRGBA },

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
	{ GUID_WICPixelFormat32bppRGB, GUID_WICPixelFormat32bppRGBA },
	{ GUID_WICPixelFormat64bppRGB, GUID_WICPixelFormat64bppRGBA },
	{ GUID_WICPixelFormat64bppPRGBAHalf, GUID_WICPixelFormat64bppRGBAHalf },
#endif
};

static DXGI_FORMAT GetDXGIFormat(const WICPixelFormatGUID& format)
{
	for (unsigned int i = 0; i < FORMAT_MAPPINGS_SIZE; ++i)
	{
		if (format == formatMappings[i].wicPixelFormat)
		{
			return formatMappings[i].dxgiFormat;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}

static WICPixelFormatGUID GetWICTargetPixelFormat(const WICPixelFormatGUID& format)
{
	for (unsigned int i = 0; i < FORMAT_CONVERSIONS_SIZE; ++i)
	{
		if (format == formatConversions[i].sourceFormat)
		{
			return formatConversions[i].targetFormat;
		}
	}

	return GUID_WICPixelFormatUndefined;
}

Image* ImageUtils::LoadWICTextureFromFilename(const wchar_t* filename)
{
	if (filename == nullptr)
	{
		return nullptr;
	}

	// Initialize COM on the current thread.
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	RefCountPtr<IWICImagingFactory> factory;

	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

	RefCountPtr<IWICBitmapDecoder> decoder;

	// Create the decoder from filename.
	hr = factory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

	if (FAILED(hr))
	{
		return nullptr;
	}

	unsigned int numFrames = 0;
	hr = decoder->GetFrameCount(&numFrames);

	if (FAILED(hr))
	{
		return nullptr;
	}

	// We, currently, do not support image formats with multiple frames.
	if (numFrames > 1)
	{
		decoder->Release();
		factory->Release();

		return nullptr;
	}

	// IWICBitmapFrameDecode represents a bitmap source and is used to access the actual bitmap data of an image format.
	RefCountPtr<IWICBitmapFrameDecode> frame;
	hr = decoder->GetFrame(0, &frame);

	if (FAILED(hr))
	{
		return nullptr;
	}

	unsigned int width = 0;
	unsigned int height = 0;

	// Retrieve the pixel width and height of the bitmap.
	hr = frame->GetSize(&width, &height);

	WICPixelFormatGUID wicFormat;
	hr = frame->GetPixelFormat(&wicFormat);

	DXGI_FORMAT dxgiFormat = GetDXGIFormat(wicFormat);

	if (dxgiFormat == DXGI_FORMAT_UNKNOWN)
	{
		// Let's see if we can convert the unsupported format to one of the supported pixel formats.
		wicFormat = GetWICTargetPixelFormat(wicFormat);
		dxgiFormat = GetDXGIFormat(wicFormat);

		if (dxgiFormat == DXGI_FORMAT_UNKNOWN)
		{
			// Unsupported format.
			return nullptr;
		}

		RefCountPtr<IWICFormatConverter> formatConverter;
		hr = factory->CreateFormatConverter(&formatConverter);

		hr = formatConverter->Initialize(frame.Get(), wicFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
	}

	RefCountPtr<IWICComponentInfo> componentInfo;
	hr = factory->CreateComponentInfo(wicFormat, &componentInfo);

	RefCountPtr<IWICPixelFormatInfo> pixelInfo;
	hr = componentInfo->QueryInterface(&pixelInfo);

	unsigned int bpp = 0;
	hr = pixelInfo->GetBitsPerPixel(&bpp);

	unsigned int pitch = (width * bpp + 7) / 8;
	unsigned int imageSize = pitch * height;
	unsigned char* buffer = new unsigned char[imageSize];

	hr = frame->CopyPixels(nullptr, pitch, imageSize, buffer);

	SubResourceData* subResources = new SubResourceData();
	subResources->initData = buffer;
	subResources->memPitch = pitch;
	subResources->memSlicePitch = 0;

	Image* texture = new Image(width, height, 0, 1, 1, TextureType::Texture2D, subResources);

	// TODO: Autogen mipmaps

	// Uninitialize COM.
	CoUninitialize();

	return texture;
}

Image* ImageUtils::LoadWICTextureFromStream(void* data, unsigned int size)
{
	if (data == nullptr || size == 0)
	{
		return nullptr;
	}

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	RefCountPtr<IWICImagingFactory> factory;

	// Create the imaging factory.
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

	RefCountPtr<IWICStream> stream;
	hr = factory->CreateStream(&stream);
	if (FAILED(hr))
	{
		CoUninitialize();
		return nullptr;
	}

	hr = stream->InitializeFromMemory(reinterpret_cast<WICInProcPointer>(data), size);

	RefCountPtr<IWICBitmapDecoder> decoder;

	// Create the decoder from filename.
	hr = factory->CreateDecoderFromStream(stream.Get(), nullptr, WICDecodeMetadataCacheOnDemand, &decoder);

	if (FAILED(hr))
	{
		return nullptr;
	}

	unsigned int numFrames = 0;
	hr = decoder->GetFrameCount(&numFrames);

	if (FAILED(hr))
	{
		return nullptr;
	}

	// We, currently, do not support image formats with multiple frames.
	if (numFrames > 1)
	{
		decoder->Release();
		factory->Release();

		return nullptr;
	}

	// IWICBitmapFrameDecode represents a bitmap source and is used to access the actual bitmap data of an image format.
	RefCountPtr<IWICBitmapFrameDecode> frame;
	hr = decoder->GetFrame(0, &frame);

	if (FAILED(hr))
	{
		return nullptr;
	}

	unsigned int width = 0;
	unsigned int height = 0;

	// Retrieve the pixel width and height of the bitmap.
	hr = frame->GetSize(&width, &height);

	WICPixelFormatGUID wicFormat;
	hr = frame->GetPixelFormat(&wicFormat);

	DXGI_FORMAT dxgiFormat = GetDXGIFormat(wicFormat);

	if (dxgiFormat == DXGI_FORMAT_UNKNOWN)
	{
		// Let's see if we can convert the unsupported format to one of the supported pixel formats.
		wicFormat = GetWICTargetPixelFormat(wicFormat);
		dxgiFormat = GetDXGIFormat(wicFormat);

		if (dxgiFormat == DXGI_FORMAT_UNKNOWN)
		{
			// Unsupported format.
			return nullptr;
		}

		RefCountPtr<IWICFormatConverter> formatConverter;
		hr = factory->CreateFormatConverter(&formatConverter);

		hr = formatConverter->Initialize(frame.Get(), wicFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
		formatConverter->Release();
	}

	RefCountPtr<IWICComponentInfo> componentInfo;
	hr = factory->CreateComponentInfo(wicFormat, &componentInfo);

	RefCountPtr<IWICPixelFormatInfo> pixelInfo;
	hr = componentInfo->QueryInterface(&pixelInfo);

	unsigned int bpp = 0;
	hr = pixelInfo->GetBitsPerPixel(&bpp);

	unsigned int pitch = (width * bpp + 7) / 8;
	unsigned int imageSize = pitch * height;
	unsigned char* buffer = new unsigned char[imageSize];

	hr = frame->CopyPixels(nullptr, pitch, imageSize, buffer);

	SubResourceData* subResources = new SubResourceData();
	subResources->initData = buffer;
	subResources->memPitch = pitch;
	subResources->memSlicePitch = 0;

	Image* texture = new Image(width, height, 0, 1, 1, TextureType::Texture2D, subResources);

	// Uninitialize COM.
	CoUninitialize();

	return texture;
}
