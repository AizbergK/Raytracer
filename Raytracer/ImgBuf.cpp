#include "ImgBuf.hpp"

#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t bfType = 0x4D42;
    uint32_t bfSize = 0;
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 54;
};

struct BMPInfoHeader {
    uint32_t biSize = 40;
    int32_t  biWidth = 0;
    int32_t  biHeight = 0;
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = 0; 
    int32_t  biXPelsPerMeter = 2835;
    int32_t  biYPelsPerMeter = 2835;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
};

#pragma pack(pop)

void ImgBuf::writeBMP(const std::string& folder_path) const {
    int bmp_count = 0;
    std::ifstream fcount(folder_path + "\\count.bin");
    if (fcount)
        fcount >> bmp_count;
    fcount.close();
    ++bmp_count;
    std::ofstream ofcount(folder_path + "\\count.bin");
    ofcount << bmp_count;
    ofcount.close();
    std::string file_name = folder_path + "\\img" + std::to_string(bmp_count) + ".bmp";
    const int rowSize = (3 * m_width + 3) & ~3; // 4-byte aligned
    const int imageSize = rowSize * m_height;

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + imageSize;
    infoHeader.biWidth = m_width;
    infoHeader.biHeight = m_height;
    infoHeader.biSizeImage = imageSize;

    std::vector<uint8_t> pixelData(imageSize);

    for (int y = m_height - 1; y >= 0; --y) {
        for (int x = 0; x < m_width; ++x) {
            int i = (m_height - 1 - y) * rowSize + x * 3;
            pixelData[i + 0] = m_img_data[y][x].z * 255;  // Blue
            pixelData[i + 1] = m_img_data[y][x].y * 255;  // Green
            pixelData[i + 2] = m_img_data[y][x].x * 255;  // Red
        }
    }

    std::ofstream out(file_name, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open file for writing");
    }

    out.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    out.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    out.write(reinterpret_cast<char*>(pixelData.data()), pixelData.size());
    out.close();
}

ImgBuf::ImgBuf(int width, int height) : m_width { width }, m_height{ height } 
{
    m_img_data = std::vector<std::vector<tuple>>(height, std::vector<tuple>(width, color(0, 0, 0)));
}

void ImgBuf::write_pixel(int width, int height, tuple color)
{
    if(height >= 0 && height < m_height && width >=0 && width < m_width)
        m_img_data[height][width] = color;
}

tuple ImgBuf::pixel_at(int width, int height)
{
    return m_img_data[height][width];
}

ImgBuf render(Camera& c, world& w)
{
    ImgBuf canvas{ c.m_hsize, c.m_vsize };

    std::vector<int> indices(canvas.m_height);
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par, indices.begin(), indices.end(), [&](int j)
    {
        for (int i = 0; i < canvas.m_width; i++)
        {
            ray r{ c.ray_for_pixel(i, j) };
            canvas.write_pixel(i, j, color_at(w, r).saturate(0.0f, 1.0f));
        }
    });

    return canvas;
}