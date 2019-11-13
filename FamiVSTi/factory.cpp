// VST3 SDKのインクルードファイル
#include "public.sdk/source/main/pluginfactory.h"

// 自作VSTのヘッダファイルをインクルード
#include "myvst3fuid.h"
#include "processor.h"

// 製作者(製作会社)の名前。終端文字「\0」含めて64文字まで。
#define MYVST_VENDOR   "SUAN"

// 製作者(製作会社)のWebサイトのURL。終端文字「\0」含めて256文字まで。
#define MYVST_URL      "https://twitter.com/ja_JP"

// 製作者(製作会社)の連絡先メールアドレス。終端文字「\0」含めて128文字まで。
#define MYVST_EMAIL    "mailto:toyanonichan@yahoo.co.jp"

// 自作するVSTの名前。終端文字「\0」含めて64文字まで。
#define MYVST_VSTNAME  "FamiVSTi"

// 自作するVSTのバージョン。終端文字「\0」含めて64文字まで。
#define MYVST_VERSION  "001" 

// 自作するVSTのカテゴリ。終端文字「\0」含めて64文字まで。
#define MYVST_SUBCATEGORIES Vst::PlugType::kInstrumentSynth


// ===================================================================================
// DLLファイルの初期化、終了処理関数
// ===================================================================================
// 基本的に何もする必要はない。
bool InitModule() { return true; }
bool DeinitModule() { return true; }


// ===================================================================================
// 自作VSTプラグインの生成
// ===================================================================================
BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

// MyVSTProcessorクラスの作成を行う
DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
	PClassInfo::kManyInstances,
	kVstAudioEffectClass,
	MYVST_VSTNAME,
	Vst::kDistributable,
	MYVST_SUBCATEGORIES,
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTProcessor::createInstance)

	END_FACTORY