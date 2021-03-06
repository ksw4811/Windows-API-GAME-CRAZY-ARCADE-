#pragma once
#include "stdafx.h"
#include "Define.h"

extern HINSTANCE hInst;                                // 현재 인스턴스입니다.
extern HWND g_hWnd;
extern RECT crt;

class BitmapImage
{
    enum IMAGE_LOAD_KIND
    {
        LOAD_RESOURCE, // 리소스로부터 생성
        LOAD_FILE,     // 파일로부터 생성
        LOAD_EMPTY,    // 그냥 생성
        LOAD_END
    };

    typedef struct tagImage
    {
        tagImage()
        {
            resID = 0;
            hMemDC = nullptr;
            hBit = nullptr;
            hOBit = nullptr;
            x = 0;
            y = 0;
            width = 0;
            height = 0;
            loadType = LOAD_RESOURCE;
        }

        DWORD resID;        // 리소스 아이디
        HDC hMemDC;         // 메모리 DC
        HBITMAP hBit;       // 비트맵(새로운 비트맵 핸들)
        HBITMAP hOBit;      // 올드 비트맵(기존 비트맵 핸들)
        float x;            // x좌표
        float y;            // y좌표
        int width;          // 이미지 가로크기
        int height;         // 이미지 세로 크기

        BYTE loadType;      // 타입
    } IMAGE_INFO, * LPIMAGE_INFO;

public:
    BitmapImage();
    ~BitmapImage();

    /* init() ==================================*/
    // 빈 비트맵 초기화
    HRESULT init(int width, int height);
    // 이미지 리소스 초기화
    HRESULT init(const DWORD resID, int width, int height, bool isTrans);

    //const char* fileName
    // 이미지 파일 초기화
    HRESULT init(const char* fileName, int width, int height, bool isTrans);
    // 프레임 이미지 파일로 초기화
    HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans);
    HRESULT init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans);

    // 릴리즈
    void release();

    /* render =======================================================================================================*/
    //그리는 녀석(일반 렌더)
    void render(HDC hdc);
    void render(HDC hdc, int destX, int destY);
    void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
    void renderStretch(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

    // 우리 추가
    // 알파 렌더
    void alphaRender(HDC hdc, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    //그리는 녀석(프레임 렌더)
    void frameRender(HDC hdc, int destX, int destY);
    void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    //그리는 녀석(루프 렌더)
    void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

    /* DC를 얻어온다 ============================================================================================= */
    inline HDC getMemDC() { return m_imageInfo->hMemDC; }

    /* 이미지의 좌표 겟셋, 이미지의 센터 좌표 세팅, 이미지의 가로세로 크기 얻기 ================================== */
    // 이미지 좌표 x 얻기
    inline float getX() { return m_imageInfo->x; }
    inline void setX(float x) { m_imageInfo->x = x; }

    // 이미지 좌표 y 얻기
    inline float getY() { return m_imageInfo->y; }
    inline void setY(float y) { m_imageInfo->y = y; }

    // 이미지 센터 좌표 세팅
    inline void setCenter(float x, float y)
    {
        m_imageInfo->x = x - (m_imageInfo->width / 2);
        m_imageInfo->y = y - (m_imageInfo->height / 2);
    }

    // 가로 세로 크기 얻기
    inline int getWidth() { return m_imageInfo->width; }
    inline int getHeight() { return m_imageInfo->height; }


    /* 바운딩 박스 (충돌용) ======================================================================================== */
    /*
    inline RECT getBoundingBox()
    {
        RECT rc;
        if (m_imageInfo->frameWidth != 0 && m_imageInfo->frameHeight != 0)
        {
            rc = makeRect(m_imageInfo->x, m_imageInfo->y, m_imageInfo->frameWidth, m_imageInfo->frameHeight);
        }
        else
        {
            rc = makeRect(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
        }
        return rc;
    }
    */



private:
    LPIMAGE_INFO m_imageInfo; //이미지 정보
    char* m_fileName; //이미지 경로 이름
    bool isTrans; // 배경색을 없앨 여부 (투명)

                           //우리추가
    BLENDFUNCTION m_blendFunc; //알파 블렌드를 위한 정보
    LPIMAGE_INFO m_blendImage; //알파 블렌드를 사용하기 위한 이미지 정보
};