import io
from google.cloud import vision
from google.cloud.vision import types

from google.oauth2 import service_account
credentials = service_account.Credentials.from_service_account_file('/home/pi/DOTnBIT/SSUOCR-ead5b6965a12.json')

import sys
reload(sys)
sys.setdefaultencoding('utf8')
path = "./Croped_Picture.jpg"

def detect_text(path):
	"""Detects text in the file."""
	client = vision.ImageAnnotatorClient(credentials=credentials)

	wri = open("./TEXT.txt",'w')

	with io.open(path, 'rb') as image_file:
		content = image_file.read()

	image = vision.types.Image(content=content)

	response = client.text_detection(image=image)
	texts = response.text_annotations
	
	wri.write('{}'.format(texts[0].description).replace('\n',""))

detect_text(path)
