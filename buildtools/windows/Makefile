# ターゲット名
TARGET_NAME = ttt

# 出力ファイル
TARGET = $(TARGET_NAME).exe

# プロジェクトルート設定
PROJ_ROOT = C:/Users/kani/Documents/GitHub/tri_engine/tri_engine


# ソース
SRCS = $(PROJ_ROOT)/source/base/tri_application.cpp

# 追加のインクルードパス
USER_INCLUDE_PATH = $(PROJ_ROOT)/include


.SUFFIXES:
.SUFFIXES: .o .cpp

LD = g++
CXX = g++

OBJS = $(SRCS:%.cpp=%.o)


# コンパイルオプション
# 追加のインクルードパス
CXXFLAGS += -I$(USER_INCLUDE_PATH)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

