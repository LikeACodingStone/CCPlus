#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libusc.h"
#include "cloudSoundsRecognition.h"

void init_speech_recognition(USC_HANDLE* handle,struct recog_params * recogParam)
{
 	int ret = usc_create_service(handle);
	if (ret != USC_ASR_OK) {
		fprintf(stderr, "usc_create_service_ext error %d\n", ret);
		return;
	}
    ret = usc_set_option((*handle), USC_OPT_ASR_APP_KEY, recogParam->appKey);
    ret = usc_set_option((*handle), USC_OPT_USER_SECRET, recogParam->secretKey);
	ret = usc_login_service(*handle);
    ret = usc_set_option((*handle), USC_OPT_INPUT_AUDIO_FORMAT, recogParam->audioFormat);
    ret = usc_set_option((*handle), USC_OPT_RECOGNITION_FIELD, recogParam->domain);	
    if (recogParam->IsUseNlu)
          ret = usc_set_option((*handle), USC_OPT_NLU_PARAMETER, recogParam->NluBuff);
}

int start_speech_recognition(USC_HANDLE handle)
{
	return usc_start_recognizer(handle);
}
int stop_speech_recognition(USC_HANDLE handle,char **lastBuff,void (*func)(char*,char**),char **resOut)
{
	int retVal = usc_stop_recognizer(handle);
	if(retVal != 0)		return retVal;
	strcat(*lastBuff,usc_get_result(handle));
//	printf("%s",*lastBuff);
	func(*lastBuff,resOut);
	return retVal;
}
void destroy_speech_recognition(USC_HANDLE handle)
{
	usc_release_service(handle);
}

void automatic_speech_recognition(USC_HANDLE handle,char *pcmBuff,int pcmLength,char **resultBuf)
{
	int ret = usc_feed_buffer(handle,pcmBuff,pcmLength);
	if (ret == USC_RECOGNIZER_PARTIAL_RESULT ||
		ret == USC_RECOGNIZER_SPEAK_END) {
		strcat(*resultBuf,usc_get_result(handle));
		printf("%s\n",*resultBuf);
	}
	else if (ret < 0) {		
		fprintf(stderr, "usc_feed_buffer error %d\n", ret);
		return;
	}
}

