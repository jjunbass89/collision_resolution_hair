# 설치
## gl3w
* gl3w 다운로드
    * git clone https://github.com/skaslev/gl3w
* python 설치
    * https://www.python.org/downloads/
    * https://stackoverflow.com/questions/14115684/how-to-set-up-gl3w-on-windows
* IDLE 실행
    * File > Open > ${ROOT}/gl3w/gl3w_gen.py
    * Run > Run module

## vtk
* vtk 빌드
    * git clone https://github.com/Kitware/VTK
    * cd VTK-9.3.0
    * mkdir build
    * cd build
    * cmake ..
    * VTK.sln 빌드.

## collision_resolution_hair
* 다운로드
    * git clone https://github.com/jjunbass89/collision_resolution_hair
* CMakeLists.txt 에 3rd party 설정
    * set(GL3W_DIR "${ROOT}/gl3w")
    * set(VTK_DIR "${ROOT}/VTK-9.3.0/build")

# 수정전 충돌 상황
* 머리나 어깨, 등과 머리카락이 충돌하거나 뜨는 것을 확인할 수 있다.
* 언리얼 엔진5로 확인함. 
    * https://www.unrealengine.com/ko/download

    [![video](https://img.youtube.com/vi/ftYdJX8hryk/0.jpg)](https://www.youtube.com/watch?v=ftYdJX8hryk)

# 수정 과정
## fbx-extract
* fbx file 에서부터 obj 파일을 추출한다.
* blender로 진행함.
    * https://www.blender.org/

## tetrahedralization
* obj 파일로부터 볼륨 메쉬를 추출한다.
* 오픈 소스로 진행함.
    * https://github.com/wildmeshing/fTetWild

## collision check

## ipc 충돌 구간 밀기
