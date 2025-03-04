# MFCApplication (Task 1)

## 📑 프로젝트 개요
MFC를 이용한 **사용자 정의 윈도우** 프로그램으로, 사용자가 클릭한 세 점을 지나가는 정원을 그립니다.  
프로그램은 다양한 기능을 제공하며, 사용자가 UI를 통해 손쉽게 조작할 수 있습니다.

---

## 🚀 **프로그램 주요 기능**
1. **점 클릭 및 드래그 기능**
    - 최대 세 개의 점을 클릭하여 생성할 수 있습니다.
    - 세 점을 모두 클릭하면 이를 지나는 정원이 자동으로 그려집니다.
    - 각 점을 클릭하고 드래그하여 실시간으로 정원이 다시 그려집니다.

2. **랜덤 이동 기능**
    - [랜덤 이동] 버튼을 누르면 점들이 **자동으로 화면 내에서 이동**합니다.
    - 이동 시 메인 UI가 **프리징되지 않도록** 별도의 스레드로 처리됩니다.
    - 초당 2회, 총 10번 **자동 반복 이동**합니다.

3. **초기화 기능**
    - [초기화] 버튼을 눌러 **모든 점과 정원을 초기화**할 수 있습니다.
    - 초기화 후, 다시 점을 클릭하여 입력할 수 있습니다.

4. **선 두께 설정**
    - 사용자 입력을 통해 **정원의 가장자리 두께**를 설정할 수 있습니다.
    - 숫자 입력만 가능하며, **유효하지 않은 입력은 처리되지 않습니다**.

5. **좌표 자동 표시**
    - 각 점의 좌표가 **자동으로 UI에 표시**됩니다.
    - 점의 색상(빨강, 파랑, 초록)에 따라 좌표 정보도 **명확하게 구분**됩니다.

---

## 📂 **폴더 구조**
```plaintext
glim-sw-assignment/
└── task1/
    ├── MFCApplication/
    │   ├── source/                           # 소스 코드 폴더
    │   │   ├── res/                          # 리소스 파일 폴더
    │   │   │   ├── MFCApplication.ico        # 아이콘 파일
    │   │   │   └── resource.rc2              # 추가 리소스 파일
    │   │   │
    │   │   ├── MFCApplication.aps            # 애플리케이션 설정 파일
    │   │   ├── MFCApplication.cpp            # 메인 애플리케이션 소스 파일
    │   │   ├── MFCApplication.h              # 메인 애플리케이션 헤더 파일
    │   │   ├── MFCApplication.rc             # 리소스 정의 파일
    │   │   ├── MFCApplication.vcxproj        # Visual Studio 프로젝트 파일
    │   │   ├── MFCApplication.vcxproj.filters # VS 프로젝트 필터 파일
    │   │   ├── MFCApplicationDlg.cpp         # 메인 다이얼로그 소스 파일
    │   │   ├── MFCApplicationDlg.h           # 메인 다이얼로그 헤더 파일
    │   │   ├── MyCustomWnd.cpp               # 사용자 정의 윈도우 소스 파일
    │   │   ├── MyCustomWnd.h                 # 사용자 정의 윈도우 헤더 파일
    │   │   ├── framework.h                   # MFC 프레임워크 헤더
    │   │   ├── pch.cpp                       # 미리 컴파일된 헤더 소스
    │   │   ├── pch.h                         # 미리 컴파일된 헤더
    │   │   ├── resource.h                    # 리소스 ID 정의 파일
    │   │   └── targetver.h                   # 대상 Windows 버전 설정 파일
    │   │
    │   ├── MFCApplication.sln                # Visual Studio 솔루션 파일
    │   │
    │   └── release/                          # 릴리즈 파일 폴더
    │       └── MFCApplication.exe            # 최종 실행 파일
    │
    └── README.md                             # 프로젝트 설명 파일