/**
 * 最简单的音视频数据处理示例
 * Simplest MediaData Test
 *
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * 本项目包含如下几种音视频测试示例
 *  (1)像素数据处理程序。包含RGB和YUV像素格式处理的函数。 
 *  (2)音频采样数据处理程序。包含PCM音频采样格式处理的函数。 
 *  (3)H.264码流分析程序。可以分离并解析NALU。 
 *  (4)AAC码流分析程序。可以分离并解析ADTS帧。 
 *  (5)FLV封装格式分析程序。可以将FLV中的MP3音频码流分离出来。 
 *  (6)UDP-RTP协议分析程序。可以将分析UDP/RTP/MPEG-TS数据包。 
 *
 * This project contains following samples to handling multimedia data:
 *  (1) Video pixel data handling program. It contains several examples to handle RGB and YUV data.
 *  (2) Audio sample data handling program. It contains several examples to handle PCM data.
 *  (3) H.264 stream analysis program. It can parse H.264 bitstream and analysis NALU of stream.
 *  (4) AAC stream analysis program. It can parse AAC bitstream and analysis ADTS frame of stream.
 *  (5) FLV format analysis program. It can analysis FLV file and extract MP3 audio stream.
 *  (6) UDP-RTP protocol analysis program. It can analysis UDP/RTP/MPEG-TS Packet.
 *
 *  Modified : ian.h
 *  Modified Date ： 2017-07-07
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Analysis H.264 Bitstream
 * @param url    Location of input H.264 bitstream file.
 */
int simplest_h264_parser(const char *url);

/**
 * Analysis FLV file
 * @param url    Location of input FLV file.
 */
int simplest_flv_parser(const char *url);

/**
 * Analysis AAC file
 * @param url    Location of input AAC file.
 */
int simplest_aac_parser(const char *url);

/**
 * Analysis RTP stream
 * @param url    RTP URL
 */
int simplest_udp_parser(int port);

/**
 * Generate RGB24 colorbar.
 * @param width    Width of Output RGB file.
 * @param height   Height of Output RGB file.
 * @param url_out  Location of Output RGB file.
 */
int simplest_rgb24_colorbar(int width, int height,const char *url_out);
/**
 * Convert RGB24 file to BMP file
 * @param rgb24path    Location of input RGB file.
 * @param width        Width of input RGB file.
 * @param height       Height of input RGB file.
 * @param url_out      Location of Output BMP file.
 */
int simplest_rgb24_to_bmp(const char *rgb24path,int width,int height,const char *bmppath);

/**
 * Split R, G, B planes in RGB24 file.
 * @param url  Location of Input RGB file.
 * @param w    Width of Input RGB file.
 * @param h    Height of Input RGB file.
 * @param num  Number of frames to process.
 *
 */
int simplest_rgb24_split(const char *url, int w, int h,int num);

/**
 * Convert RGB24 file to YUV420P file
 * @param url_in  Location of Input RGB file.
 * @param w       Width of Input RGB file.
 * @param h       Height of Input RGB file.
 * @param num     Number of frames to process.
 * @param url_out Location of Output YUV file.
 */
int simplest_rgb24_to_yuv420(const char *url_in, int w, int h,int num,const char *url_out);

/**
 * Generate YUV420P gray scale bar.
 * @param width    Width of Output YUV file.
 * @param height   Height of Output YUV file.
 * @param ymin     Max value of Y
 * @param ymax     Min value of Y
 * @param barnum   Number of bars
 * @param url_out  Location of Output YUV file.
 */
int simplest_yuv420_graybar(int width, int height,int ymin,int ymax,int barnum,const char *url_out);

/**
 * Convert YUV420P file to gray picture
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param num     Number of frames to process.
 */
int simplest_yuv420_gray(const char *url, int w, int h,int num);

/**
 * Split Y, U, V planes in YUV420P file.
 * @param url  Location of Input YUV file.
 * @param w    Width of Input YUV file.
 * @param h    Height of Input YUV file.
 * @param num  Number of frames to process.
 *
 */
int simplest_yuv420_split(const char *url, int w, int h,int num);

/**
 * Halve Y value of YUV420P file
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param num     Number of frames to process.
 */
int simplest_yuv420_halfy(const char *url, int w, int h,int num);

/**
 * Add border for YUV420P file
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param border  Width of Border.
 * @param num     Number of frames to process.
 */
int simplest_yuv420_border(const char *url, int w, int h,int border,int num);


/**
 * Calculate PSNR between 2 YUV420P file
 * @param url1     Location of first Input YUV file.
 * @param url2     Location of another Input YUV file.
 * @param w        Width of Input YUV file.
 * @param h        Height of Input YUV file.
 * @param num      Number of frames to process.
 */
int simplest_yuv420_psnr(const char *url1,const char *url2,int w,int h,int num);

/**
 * Split Y, U, V planes in YUV444P file.
 * @param url  Location of YUV file.
 * @param w    Width of Input YUV file.
 * @param h    Height of Input YUV file.
 * @param num  Number of frames to process.
 *
 */
int simplest_yuv444_split(const char *url, int w, int h,int num);

/**
 * Cut a 16LE PCM single channel file.
 * @param url        Location of PCM file.
 * @param start_num  start point
 * @param dur_num    how much point to cut
 */
int simplest_pcm16le_cut_singlechannel(const char *url,int start_num,int dur_num);

/**
 * Split Left and Right channel of 16LE PCM file.
 * @param url  Location of PCM file.
 *
 */
int simplest_pcm16le_split(const char *url);

/**
 * Halve volume of Left channel of 16LE PCM file
 * @param url  Location of PCM file.
 */
int simplest_pcm16le_halfvolumeleft(const char *url);

/**
 * Re-sample to double the speed of 16LE PCM file
 * @param url  Location of PCM file.
 */
int simplest_pcm16le_doublespeed(const char *url);

/**
 * Convert PCM-16 data to PCM-8 data.
 * @param url  Location of PCM file.
 */
int simplest_pcm16le_to_pcm8(const char *url);

/**
 * Convert PCM16LE raw data to WAVE format
 * @param pcmpath      Input PCM file.
 * @param channels     Channel number of PCM file.
 * @param sample_rate  Sample rate of PCM file.
 * @param wavepath     Output WAVE file.
 */
int simplest_pcm16le_to_wave(const char *pcmpath,int channels,int sample_rate,const char *wavepath);



static int
get_input_num (void)
{
	int ret=-1;
	char get_buf[32]={0};
	if((ret =scanf("%s",get_buf)) <= 0)
	{
		printf ("scanf error\n");
		return -1;
	}
#ifdef GET_NUM
	return atoi(get_buf);
#else
	return get_buf[0];
#endif
}


int main(int argc, char* argv[]){

    while (1)
	{
		printf ("1: yuv420 split ..\n");
		printf ("2: yuv444 split ..\n");
		printf ("3: yuv420 halfy ..\n");
		printf ("4: yuv420 gray  ..\n");
		printf ("5: yuv420 border..\n");
		printf ("6: yuv420 graybar..\n");
		printf ("7: yuv420 psnr  ..\n");
		printf ("h: h.264  parser..\n");
		printf ("a: aac    parser..\n");
		printf ("f: flv    parser..\n");

		int select = get_input_num();
		switch (select)
		{
			case '1':
			simplest_yuv420_split("lena_256x256_yuv420p.yuv",256,256,1);
			break;
			case '2':
			simplest_yuv444_split("lena_256x256_yuv444p.yuv",256,256,1);
			break;
			case '3':
			simplest_yuv420_halfy("lena_256x256_yuv420p.yuv",256,256,1);
			break;
			case '4':
			simplest_yuv420_gray("lena_256x256_yuv420p.yuv",256,256,1);
			break;
			case '5':
			simplest_yuv420_border("lena_256x256_yuv420p.yuv",256,256,20,1);
			break;
			case '6':
            simplest_yuv420_graybar(640, 360,0,255,10,"graybar_640x360.yuv");
			break;
			case '7':
			simplest_yuv420_psnr("lena_256x256_yuv420p.yuv","lena_distort_256x256_yuv420p.yuv",256,256,1);
			break;
			case 'h':
			simplest_h264_parser("sintel.h264");
			break;
			case 'a':
			simplest_aac_parser("nocturne.aac");
			break;
			case 'f':
            simplest_flv_parser("cuc_ieschool.flv");
			break;
			default:
			break;
		}

	continue;

	simplest_rgb24_split("cie1931_500x500.rgb", 500, 500,1);

	simplest_rgb24_to_bmp("lena_256x256_rgb24.rgb",256,256,"output_lena.bmp");

	simplest_rgb24_to_yuv420("lena_256x256_rgb24.rgb",256,256,1,"output_lena.yuv");

	simplest_rgb24_colorbar(640, 360,"colorbar_640x360.rgb");

	simplest_pcm16le_split("NocturneNo2inEflat_44.1k_s16le.pcm");

	simplest_pcm16le_halfvolumeleft("NocturneNo2inEflat_44.1k_s16le.pcm");

	simplest_pcm16le_doublespeed("NocturneNo2inEflat_44.1k_s16le.pcm");

	simplest_pcm16le_to_pcm8("NocturneNo2inEflat_44.1k_s16le.pcm");

	simplest_pcm16le_cut_singlechannel("drum.pcm",2360,120);

	simplest_pcm16le_to_wave("NocturneNo2inEflat_44.1k_s16le.pcm",2,44100,"output_nocturne.wav");

	simplest_udp_parser(8880);
	}

	return 0;
}