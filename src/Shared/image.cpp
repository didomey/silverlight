#include <jpeglib.h>

std::vector<uint8_t> generateJPEG(std::vector<uint8_t>& buffer, unsigned int width, unsigned int height, unsigned int quality) {
	struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);

    unsigned char* jpegBuffer = nullptr;
    size_t jpegSize = 0;

    jpeg_mem_dest(&cinfo, &jpegBuffer, &jpegSize);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3; // RGB
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    int row_stride = width * 3; // 3 bytes per pixel (RGB)
    JSAMPROW row_pointer;
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer = &buffer[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);

    jpeg_destroy_compress(&cinfo);

	std::vector<unsigned char> jpegBufferVec(jpegBuffer, jpegBuffer + jpegSize);
	std::vector<uint8_t> jpegBufferFinalVec(jpegBufferVec);

    return jpegBufferFinalVec;
}
