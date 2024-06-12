from django.shortcuts import render


#class Custom404Middleware:
#    def __init__(self, get_response):
#        self.get_response = get_response
#
#    def __call__(self, request):
#        response = self.get_response(request)
#        if response.status_code == 404:
#            # Se la view richiesta non è stata trovata, restituisci una pagina HTML personalizzata
#            return render(request, 'page/index.html', status=404)
#        return response
