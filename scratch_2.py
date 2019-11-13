"""
ATTRIBUTION DES VALEURS

mh = moteur pince du haut                                         mh = -1  ==> moteur allumé dans sens inverse
mb = moteur pince du bas                                          mb = 0   ==> moteur éteint
mp = moteur principal                                             mp = 1   ==> moteur allumé


deth = detecteur IR du haut                                       deth = 0  ==> detecteur capte rien    (True False ?)
detb = detecteur IR du bas                                        detb = 1  ==> detecteur capte qqch

contacth = detecteur de contact pince haut                        contacth = 1  ==> la pince du haut est accrochée
contactb = detecteur de contact pince bas                         contactb = 0  ==> la pince du bas n'est pas accrochée

contactf = detecteur de contact final (en bas)


Test
"""

BON_SENS = 1
ARRET = 0
SENS_INVERSE = 1

positionh = 5
positionb = 0
echelle = ['B', '', '', '', '', 'H', '', '', '', '', '', '|', '', '', '', '', '', '|', '', '', '', '', '', '|', '', '',
           '', '', '', '|', '', '', '', '', '_', '|']
echellefixe = (
'', '', '', '', '', '|', '', '', '', '', '', '|', '', '', '', '', '', '|', '', '', '', '', '', '|', '', '', '', '', '',
'|', '', '', '', '', '', '|')


class servomoteur:
    def __init__(self):
        self.volt = 0

    def voltage(self, volt):
        self.volt = volt

    def rotation(self, angle):
        volt = angle
        self.volt += volt

class moteur:
    def __init__(self):
        self.volt = 0
        self.etat = 0

    def tourner(self, sens):
        self.etat = sens

    def stop(self):
        self.etat = ARRET


class capteur:
    def __init__(self, statut, position):
        self.statut = statut
        self.position = position

    def detecte(self):
        if echelle[self.position] == '|':
            return True



class robot:
    def __init__(self):
        self.mp = moteur()
        self.mh = servomoteur()
        self.mb = servomoteur()
        self.cib = capteur(False, positionb)
        self.cih = capteur(False, positionh)
        """"self.ci_haut ="""
        self.cch = capteur(True, positionh)
        self.ccb = capteur(True, positionb)
        """""self.cc_haut =
        self.cc_bas = """


    def monterhaut():
        """
            fonction qui decroche ,
            fait monter la pince du haut,
            s'arrête lorsque le detecteur IR
            capte une barre et s'accroche
            dessus
            """
        self.mh.rotation(-90)
        """echelle[position] = 'h'
        printechelle(echelle)"""
        self.mp.tourner(BON_SENS)
        self.ch.position += 1
        while not self.ch.detecte():
            self.ch.position += 1
            """echelle[position] = 'h'
            echelle[position - 1] = echellefixe[position - 1]
            printechelle(echelle)
            position += volt"""
        self.mp.stop()
        self.mh.rotation(90)
        """echelle[position - 1] = 'H'
        printechelle(echelle)"""

    def monterbas(position, volt):
        self.mb.rotation(-90)
        '''echelle[position] = 'b'
        printechelle(echelle)'''
        self.mp.tourner(BON_SENS)
        while not self.cb.detecte():
            """echelle[position] = 'b'
            echelle[position - 1] = echellefixe[position - 1]
            printechelle(echelle)"""
            self.cb.position += 1
        self.mp.stop()
        self.mb.rotation(90)
        """echelle[position - 1] = 'B'
        printechelle(echelle)"""

    def montee(self):
        """while not self.ci_haut.state:
            self.monterhaut()
            self.monterbas()"""


     """def printechelle(echelle):
        for i in len(echelle):
            print(i, end=' ')
        print('\n')"""





"""robot.printechelle(echelle)

robot.monterhaut(positionh, 1)
robot.monterbas(positionb, 1)"""
