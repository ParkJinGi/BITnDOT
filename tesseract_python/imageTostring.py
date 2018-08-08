from PIL import Image       # pip install pillow
from pytesseract import *   # pip install pytesseract
import configparser
import os

# Init Config Parser
config = configparser.ConfigParser()
# Read Config File
config.read(os.path.dirname(os.path.realpath(__file__)) + os.sep + 'envs' + os.sep + 'property.ini')


# Image to String
def ocrToStr(fullPath, outTxtPath, fileName, lang='eng'):  # default : English

    # Path of Image
    img = Image.open(fullPath)
    txtName = os.path.join(outTxtPath, fileName.split('.')[0])

    # Extract (ImageFile, Language, Option)
    # preserve_interword_spaces : 단어 간격 옵션을 조절하면서 추출 정확도를 확인한다.
    # psm(페이지 세그먼트 모드 : 이미지 영역안에서 텍스트 추출 범위 모드)
    # psm mode : https://github.com/tesseract-ocr/tesseract/wiki/Command-Line-Usage
    outText = image_to_string(img, lang=lang, config='--psm 1 -c preserve_interword_spaces=1')

    print('+++ OCR Extract Result +++')
    print('Extract FileName ->>> : ', fileName, ' : <<<-')
    print('\n\n')

    print(outText)

    # Write extracted contents to Text file
    strToTxt(txtName, outText)


# Save String as Text file
def strToTxt(txtName, outText):
    with open(txtName + '.txt', 'w', encoding='utf-8') as f:
        f.write(outText)


if __name__ == "__main__":

    # Text file 저장경로
    outTxtPath = os.path.dirname(os.path.realpath(__file__)) + config['Path']['OcrTxtPath']

    # OCR 추출 작업 메인
    for root, dirs, files in os.walk(os.path.dirname(os.path.realpath(__file__)) + config['Path']['OriImgPath']):
        for fname in files:
            fullName = os.path.join(root, fname)
            # Extract : Kor, Eng, Kor+Eng
            ocrToStr(fullName, outTxtPath, fname, 'kor+eng')
