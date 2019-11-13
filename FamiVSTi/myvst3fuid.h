#pragma once
// VST3 SDKのインクルードファイル
#include "pluginterfaces\base\funknown.h"

// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		// FUIDの生成
		static const FUID ProcessorUID(0x837BB17F, 0x50B040A4, 0x80B7BEF4, 0x2FD2F208);
		static const FUID ControllerUID(0x837BB17F, 0x50B040A4, 0x80B7BEF4, 0x2FD2F208);
	}
} // namespace SteinbergとVstの終わり