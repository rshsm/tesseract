#include <tesseract\baseapi.h>
#include <leptonica\allheaders.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
 
    // Initialize tesseract-ocr with English, without specifying tessdata path.
    if (api->Init(NULL, "eng")) 
    {
        api->End();
 
        return 1;
    }
 
    // Open input image with leptonica library
    Pix *image;
    if((image = pixRead("rp.jpg")) == NULL)
    {
        api->End();
 
        return 2;
    }
     
    api->SetImage(image);
     
    if(api->Recognize(NULL) < 0)
    {
        api->End();
        pixDestroy(&image);
 
        return 3;
    }
 
    int confidence = api->MeanTextConf();
    printf("Confidence: %d\n", confidence);
    if(confidence < 80)
        printf("\n");
 
    tesseract::ResultIterator *it = api->GetIterator();
 
    do
    {
        printf("\n");
        if(it->Empty(tesseract::RIL_PARA))
            continue;
 
        char *para_text = it->GetUTF8Text(tesseract::RIL_PARA);
        printf("%s", para_text);
        //delete[] para_text;
    } while (it->Next(tesseract::RIL_PARA));
   
    delete it;
 
    api->End();
    pixDestroy(&image);
 
    return 0;

	}