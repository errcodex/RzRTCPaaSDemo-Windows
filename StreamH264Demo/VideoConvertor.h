#pragma once
#include <functional>
#include <memory>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}


// 临时用
#include "VideoDecoder.h"
// end

class VideoConvertor
{
public:
	VideoConvertor(int width = 1280, int height = 720);
	~VideoConvertor() = default;
	bool encode(const uint8_t* buffer, uint8_t** out, int& size, bool& isKey);
	bool decode(const uint8_t* buffer, int data_size, std::function<void(uint8_t*, int, int)> cb);

	// 临时用
	std::shared_ptr<VideoDecoder> vdecoder;
	// end

private:
	// 解码用与输入
	int inbufSize = 0;
	std::shared_ptr<uint8_t[]> inbuf;

private:
	class Encoder
	{
	public:
		Encoder(int width = 1280, int height = 720);
		~Encoder();
		bool convert(const uint8_t* buffer, uint8_t** out, int& size, bool& isKey);

	private:
		const AVCodec* codec = nullptr;
		AVCodecContext* c = nullptr;
		AVFrame* frame = nullptr;
		AVPacket* pkt = nullptr;
		uint32_t pts = 0;
	};

	class Decoder
	{
	public:
		Decoder();
		~Decoder();
		bool convert(const std::shared_ptr<uint8_t[]> inbuf, int data_size, std::function<void(uint8_t*, int, int)> cb);

	private:
		const AVCodec* codec = nullptr;
		AVCodecParserContext* parser = nullptr;
		AVCodecContext* c = nullptr;
		AVFrame* frame = nullptr;
		AVPacket* pkt = nullptr;
	};


private:
	std::shared_ptr<VideoConvertor::Encoder> encoder;
	std::shared_ptr<VideoConvertor::Decoder> decoder;
};