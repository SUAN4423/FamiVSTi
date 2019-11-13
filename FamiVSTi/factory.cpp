// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/main/pluginfactory.h"

// ����VST�̃w�b�_�t�@�C�����C���N���[�h
#include "myvst3fuid.h"
#include "processor.h"

// �����(������)�̖��O�B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_VENDOR   "SUAN"

// �����(������)��Web�T�C�g��URL�B�I�[�����u\0�v�܂߂�256�����܂ŁB
#define MYVST_URL      "https://twitter.com/ja_JP"

// �����(������)�̘A���惁�[���A�h���X�B�I�[�����u\0�v�܂߂�128�����܂ŁB
#define MYVST_EMAIL    "mailto:toyanonichan@yahoo.co.jp"

// ���삷��VST�̖��O�B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_VSTNAME  "FamiVSTi"

// ���삷��VST�̃o�[�W�����B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_VERSION  "001" 

// ���삷��VST�̃J�e�S���B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_SUBCATEGORIES Vst::PlugType::kInstrumentSynth


// ===================================================================================
// DLL�t�@�C���̏������A�I�������֐�
// ===================================================================================
// ��{�I�ɉ�������K�v�͂Ȃ��B
bool InitModule() { return true; }
bool DeinitModule() { return true; }


// ===================================================================================
// ����VST�v���O�C���̐���
// ===================================================================================
BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

// MyVSTProcessor�N���X�̍쐬���s��
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