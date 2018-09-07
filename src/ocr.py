import io
from google.cloud import vision
from google.cloud.vision import types

import sys
reload(sys)
sys.setdefaultencoding('utf8')
path = "./tmp.jpg"
#path = './images.png'

def detect_text(path):
	"""Detects text in the file."""
	client = vision.ImageAnnotatorClient()

	wri = open("./TEXT.txt",'w')

	with io.open(path, 'rb') as image_file:
		content = image_file.read()

	image = vision.types.Image(content=content)

	response = client.text_detection(image=image)
	texts = response.text_annotations
	
	wri.write('{}'.format(texts[0].description).replace('\n',""))
#	for text in texts:
#		print('{}'.format(text.description))
#		wri.write('{}'.format(text.description))

detect_text(path)
