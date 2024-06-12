from	dotenv	import load_dotenv

from	django.shortcuts		import render
from	django.middleware.csrf	import get_token

def main_page(request):
	load_dotenv()
	token = get_token(request)
	response = render(request, 'page/index.html')
	response.set_cookie('csrftoken', token)

	return response