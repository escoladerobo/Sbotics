inicio
	AbrirConsole()
#  Destrava Motores
	TravarMotor("l", falso)
	TravarMotor("r", falso)
# Liga motores na velocidade 200
	Motor("l", 200)
	Motor("r", 200)
# Identifica obstaculo
	enquanto ( Ultrassonico("us") > 6 ) farei {
		EscreverLinha( VirarTexto( Ultrassonico("us") ) )
		Esperar(500)
	}
	EscreverLinha("Obstaculo!")
# Escreve a distancia lida pelo sensor ultrassonico
	EscreverLinha( VirarTexto( Ultrassonico("us") ) )
# Para o motor da direita para virar 90 graus a direita
	Motor("r", 0)
	EscreverLinha("1 - Direita")
# 1 - Espera ele virar a direita
	Esperar(15000)
# 2 - Vai para Frente
	Motor("l", 200)
	Motor("r", 200)
	EscreverLinha("2 - Frente")
	Esperar(500)
# 3 - Virar 90 graus a esquerda
	Motor("l", 0)
	Motor("r", 200)
	EscreverLinha("3 - Esquerda")
	Esperar(15000)
# 4 - Vai pra Frente
# 5 - Vai pra Frente
	Motor("l", 200)
	Motor("r", 200)
	EscreverLinha("4 - Frente")
	Esperar(500)
	EscreverLinha("5 - Frente")
	Esperar(500)
# 6 - Vira 90 graus a esquerda
	Motor("l", 0)
	Motor("r", 200)
	EscreverLinha("6 - Esquerda")
	Esperar(15000)
# 7 - Vai para Frente
	Motor("l", 200)
	Motor("r", 200)
	EscreverLinha("7 - Frente")
	Esperar(1000)
# 8 - Vira 90 graus a direita
	Motor("l", 200)
	Motor("r", 0)
	EscreverLinha("8 - Direita")
	Esperar(11000)
# 9 - Vai para Frente
	Motor("l", 200)
	Motor("r", 200)
	EscreverLinha("9 - Frente")
	Esperar(8000)
# 10 - Parar
	Motor("l", 0)
	Motor("r", 0)
	EscreverLinha("10 - Parar")
fim