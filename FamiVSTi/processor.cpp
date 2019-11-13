// ����VST�p�̃C���N���[�h�t�@�C��
#include "myvst3fuid.h"
#include "processor.h"

// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// �N���X������������֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
		{
			// �܂��p�����N���X�̏����������{
			tresult result = AudioEffect::initialize(context);
			if (result == kResultTrue)
			{
				// ���͂Əo�͂�ݒ�
				addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

				// ���͂�EventBus��ǉ�����
				addEventInput(STR16("Event Input"), 1);

				// �ȉ��ŗL�̏����������{�B
				volume = 0.0f;
				theta = 0.0f;
				pitchList.clear();
			}


			// �����������������kResultTrue��Ԃ��B
			return result;
		}

		tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
		{
			// input��output�̃o�X��1���ŁA����input��output�̍\�����X�e���I�̏ꍇ
			if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
			{
				return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
			}

			// �Ή����Ă��Ȃ��o�X�\���̏ꍇ�AkResultFalse��Ԃ��B
			return kResultFalse;
		}

		// ===================================================================================
		// �����M������������֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
		{
			// �p�����[�^�[�ύX�̏���
			// �^����ꂽ�p�����[�^�[������Ƃ��Adata��inputParameterChanges��
			// IParameterChanges�N���X�ւ̃|�C���^�̃A�h���X������
			if (data.inputParameterChanges != NULL)
			{
				// �^����ꂽ�p�����[�^�[�̐����擾
				int32 paramChangeCount = data.inputParameterChanges->getParameterCount();

				// �^����ꂽ�p�����[�^�[���A�������J��Ԃ��B
				for (int32 i = 0; i < paramChangeCount; i++)
				{
					// �p�����[�^�[�ύX�̃L���[���擾
					// (��������T���v�����ɕ����̃p�����[�^�[�ύX��񂪂���\�������邽�߁A
					// �L���[�Ƃ����`�ɂȂ��Ă���B)
					IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);
					if (queue != NULL)
					{
						// �ǂ̃p�����[�^�[���ύX���ꂽ���m�邽�߁A�p�����[�^�[tag���擾
						int32 tag = queue->getParameterId();

						// �ύX���ꂽ�񐔂��擾
						int32 valueChangeCount = queue->getPointCount();
						ParamValue value;
						int32 sampleOffset;

						// �Ō�ɕύX���ꂽ�l���擾
						if (queue->getPoint(valueChangeCount - 1, sampleOffset, value) == kResultTrue)
						{
							// tag�ɉ��������������{
							switch (tag)
							{
								// ����̓p�����[�^���Ȃ��̂ŉ������Ȃ�
							}
						}
					}
				}
			}

			// �C�x���g�̏���
			// �^����ꂽ�C�x���g������Ƃ�data��inputEvents��
			// IEventList�N���X�ւ̃|�C���^�̃A�h���X������
			IEventList* eventList = data.inputEvents;
			if (eventList != NULL)
			{
				// �C�x���g�̐����擾����B
				int32 numEvent = eventList->getEventCount();
				for (int32 i = 0; i < numEvent; i++)
				{
					// i�Ԗڂ̃C�x���g�f�[�^���擾����
					Event event;
					if (eventList->getEvent(i, event) == kResultOk)
					{
						int16 channel;
						int16 noteNo;
						float velocity;

						// �C�x���g�f�[�^�̃^�C�v���ƂɐU�蕪��
						switch (event.type)
						{
						case Event::kNoteOnEvent: // �m�[�g�I���C�x���g�̏ꍇ
							channel = event.noteOn.channel;
							noteNo = event.noteOn.pitch;
							velocity = event.noteOn.velocity;

							onNoteOn(channel, noteNo, velocity);

							break;

						case Event::kNoteOffEvent: // �m�[�g�I�t�C�x���g�̏ꍇ
							channel = event.noteOff.channel;
							noteNo = event.noteOff.pitch;
							velocity = event.noteOff.velocity;

							onNoteOff(channel, noteNo, velocity);
							break;
						}
					}
				}
			}

			// ���́E�o�̓o�b�t�@�̃|�C���^���킩��₷���ϐ��Ɋi�[
			// inputs[]�Aoutputs[]��AudioBus�̐���������(addAudioInput()�AaddAudioOutput()�Œǉ�����������)
			// �����AudioBus��1�����Ȃ̂� 0 �݂̂ƂȂ�
			// channelBuffers32��32bit���������_�^�̃o�b�t�@�ŉ����M���̃`�����l����������
			// ���m����(kMono)�Ȃ� 0 �݂̂ŁA�X�e���I(kStereo)�Ȃ� 0(Left) �� 1(Right) �ƂȂ�
			Sample32* outL = data.outputs[0].channelBuffers32[0];
			Sample32* outR = data.outputs[0].channelBuffers32[1];

			// numSamples�Ŏ������T���v�����A��������������
			for (int32 i = 0; i < data.numSamples; i++)
			{
				// �I�V���[�^�[�̉������擾����B
				float pitch = 0.0f;

				// �������X�g�̃T�C�Y��0�łȂ��ꍇ
				if (pitchList.size() != 0)
				{
					// �Ō�ɉ����ꂽMIDI�m�[�g�̉������擾����
					pitch = pitchList[pitchList.size() - 1];
				}

				// �p�x�Ƃɉ����ɉ������p���x��������
				// (�����ł̓T���v�����[�g44100Hz�Œ�Ōv�Z���Ă���̂ŕK�v�ɉ����ď�������)
				theta += (2.0f * 3.14159265f * pitch) / 44100.0f;

				// �{�����[���ƃI�V���[�^(sin()�֐�)�̒l(�U��)���v�Z���ďo�͂���
				// (�ˑR�傫�ȉ����ł�Ƃ܂����̂łƂ肠����0.3f���|���Ă���)
				outL[i] = 0.3f * volume * sin(theta);
				outR[i] = 0.3f * volume * sin(theta);
			}

			// ���Ȃ����kResultTrue��Ԃ�(�����炭�K��kResultTrue��Ԃ�)
			return kResultTrue;
		}

		void MyVSTProcessor::onNoteOn(int channel, int note, float velocity)
		{
			// MIDI�m�[�g�I���C�x���g�̏������s��

			// �ȒP�ȃT���v���Ȃ̂ŁAchannel��velocity�͖�������

			// �����ꂽ�m�[�g����A�������v�Z
			// �m�[�gNo.69��440Hz�ɂȂ�B�������Ɍv�Z����B
			// �v�Z���̏ڍא����ɂ��Ă͊���
			float pitch = (440.0f * powf(2.0f, (float)(note - (69)) / 12.0));

			// pitchList�̍Ō�ɒǉ�����
			pitchList.push_back(pitch);

			// �{�����[����0.0f���Ɖ����o�Ȃ��̂ł�1.0f�ɂ��Ă���
			volume = 1.0f;

		}

		void MyVSTProcessor::onNoteOff(int channel, int note, float velocity)
		{
			// MIDI�m�[�g�I�t�C�x���g�̏������s��

			// �ȒP�ȃT���v���Ȃ̂ŁAchannel��velocity�͖�������

			// �����ꂽ�m�[�g����A�������v�Z
			float pitch = (440.0f * powf(2.0f, (float)(note - (69)) / 12.0));

			// pitchList���ŏ����猟�����Apitch�ɍ��v������̂��폜����
			for (int i = 0; i < (int)pitchList.size(); i++)
			{
				if (pitchList[i] == pitch)
				{
					// pitch�ƍ��v������̂��������ꍇ�A
					// �Y������f�[�^����菜���Č������I������
					pitchList.erase(pitchList.begin() + i);
					break;
				}
			}

			// pitchList�̃T�C�Y��0�̏ꍇ�A�܂艟���ꂽ�m�[�g���Ȃ��ꍇ�A
			// �{�����[����0.0f�ɂ��ĉ�������
			if (pitchList.size() == 0)
			{
				volume = 0.0f;
			}

		}

	}
} // namespace Steinberg��Vst�̏I���