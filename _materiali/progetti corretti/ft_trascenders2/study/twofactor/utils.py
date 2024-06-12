def mailCheck(stringa):
    if not stringa:
        return True
    
    validChar = set('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
    indice_at = stringa.find('@')
    indice_punto = stringa.find('.', indice_at)
    
    if indice_at > 0 and indice_punto > indice_at + 1 and any(char in validChar for char in stringa[:indice_at]) and \
            any(char in validChar for char in stringa[indice_at + 1:indice_punto]) and \
            any(char in validChar for char in stringa[indice_punto + 1:]):
        return True
    else:
        return False