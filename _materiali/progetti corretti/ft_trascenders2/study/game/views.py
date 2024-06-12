import	json

from	django.http				import JsonResponse
from	django.utils.timezone	import now
from	django.core.serializers	import serialize

from	.models					import Match
from	page.models				import ZongUser
from	usermanagement.utils	import checkJWTValidity, returnJwtResponse

def showWinner(request):
	if request.method == 'POST':

		isJtwValid = checkJWTValidity(request, request.user.username)
		if (isJtwValid != 0):
			return returnJwtResponse(isJtwValid)
	
		data = json.loads(request.body)
		#print (data)
		winner = data.get('winner')
		s1 = data.get('swinner')
		loser = data.get('loser')
		s2 = data.get('sloser')
		winner = ZongUser.objects.get(username=winner)
		loser = ZongUser.objects.get(username=loser)
		match = Match.objects.create(winner=winner.username, loser=loser.username, date=now(), score=f'{s1} : {s2}')
		winner.game_won += 1
		winner.game_total += 1
		loser.game_total += 1
		winner.matches.add(match)
		loser.matches.add(match)
		match.save()
		winner.save()
		loser.save()
		return JsonResponse({'mess': 'tuttoko'})
	
def getMatchData(request):
	if request.method == 'GET':

		isJtwValid = checkJWTValidity(request, request.user.username)
		if (isJtwValid != 0):
			return returnJwtResponse(isJtwValid)

		
		user = ZongUser.objects.get(username=request.user.username)
		user_matches = user.matches.all()
		matches = []
		for match in user_matches:
			matches.append({"winner" : match.winner, "loser" : match.loser, "score": match.score, "date" : match.date})
		response = {
			'matches': matches,
		}
		return JsonResponse(response)
