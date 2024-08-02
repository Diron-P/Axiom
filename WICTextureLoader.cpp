#include <wincodec.h>
#include "WICTextureLoader.h"

constexpr auto FORMAT_MAPPINGS_SIZE = 17;

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
	{ GUID_WICPixelFormat16bppBGR565, DXGI_FORMAT_B5G6R5_UNORM  },
	{ GUID_WICPixelFormat32bppGrayFloat, DXGI_FORMAT_R32_FLOAT },
	{ GUID_WICPixelFormat16bppGrayHalf, DXGI_FORMAT_R16_FLOAT },
	{ GUID_WICPixelFormat16bppGray, DXGI_FORMAT_R16_UNORM },
	{ GUID_WICPixelFormat8bppGray, DXGI_FORMAT_R8_UNORM },
	{ GUID_WICPixelFormat8bppAlpha, DXGI_FORMAT_A8_UNORM },
	{ GUID_WICPixelFormat96bppRGBFloat, DXGI_FORMAT_R32G32B32_FLOAT },
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

void Axiom::LoadTextureFromFilename(const wchar_t* filename)
{
	if (filename == nullptr)
	{
		return;
	}

	// Initialize COM on the current thread.
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	IWICImagingFactory* factory = nullptr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

	IWICBitmapDecoder* decoder = nullptr;

	// Create the decoder from filename.
	hr = factory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

	if (FAILED(hr))
	{
		return;
	}

	unsigned int numFrames = 0;
	hr = decoder->GetFrameCount(&numFrames);

	if (FAILED(hr))
	{
		return;
	}

	// We, currently, do not support image formats with multiple frames.
	if (numFrames > 1)
	{
		decoder->Release();
		factory->Release();

		return;
	}

	// IWICBitmapFrameDecode represents a bitmap source and is used to access the actual bitmap data of an image format.
	IWICBitmapFrameDecode* frame = nullptr;
	hr = decoder->GetFrame(0, &frame);

	if (FAILED(hr))
	{
		return;
	}

	unsigned int width = 0;
	unsigned int height = 0;

	// Retrieve the pixel width and height of the bitmap.
	hr = frame->GetSize(&width, &height);

	WICPixelFormatGUID wicFormat;
	hr = frame->GetPixelFormat(&wicFormat);

	DXGI_FORMAT dxgiFormat = GetDXGIFormat(wicFormat);
	
	IWICComponentInfo* componentInfo;
	hr = factory->CreateComponentInfo(wicFormat, &componentInfo);
	
	IWICPixelFormatInfo* pixelInfo;
	hr = componentInfo->QueryInterface(&pixelInfo);

	unsigned int bpp = 0;
	hr = pixelInfo->GetBitsPerPixel(&bpp);

	unsigned int stride = (width * bpp + 7) / 8;



	// Uninitialize COM.
	CoUninitialize();
}

void Axiom::LoadTextureFromStream(const void* buffer, unsigned int size)
{
	if (buffer == nullptr || size == 0)
	{
		return;
	}

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	IWICImagingFactory* factory = nullptr;

	// Create the imaging factory.
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
}
