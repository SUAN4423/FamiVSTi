#pragma once

// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/ivstevents.h"

// ����VST�p�̃C���N���[�h�t�@�C��
//#include "myvst3define.h"

// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		// ===================================================================================
		// �����M������������Processor�N���X
		// ===================================================================================
		class MyVSTProcessor : public AudioEffect
		{
		protected:
			ParamValue  volume; // �I�V���[�^�̉���
			std::vector<float> pitchList; // �����ꂽ�L�[�̉���(���g��)��ۑ�����ϒ��z��

			ParamValue theta; // �I�V���[�^�Ƃ��Ďg�p����SIN�֐��̊p�x��
		public:
			// �N���X������������֐�(�K�{)
			tresult PLUGIN_API initialize(FUnknown* context);

			// �o�X�\����ݒ肷��֐��B
			tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

			// �����M������������֐�(�K�{)
			tresult PLUGIN_API process(ProcessData& data);

			// ����֐�
			// MIDI�m�[�g�I���C�x���g�AMIDI�m�[�g�I�t�C�x���g���󂯎�����ꍇ�ɏ�������֐�
			virtual void onNoteOn(int channel, int note, float velocity);
			virtual void onNoteOff(int channel, int note, float velocity);

			// ����VST Processor�N���X�̃C���X�^���X���쐬���邽�߂̊֐�(�K�{)
			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
		};


	}
} // namespace Steinberg��Vst�̏I���