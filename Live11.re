funcao numero moveFrente(numero vel) {
	Motor("l", vel)
	Motor("r", vel)
	retornar (0)
}
funcao numero moveEsquerdaPouco(numero vel) {
	Motor("l", 0)
	Motor("r", vel)
	retornar (1)
}
funcao numero moveDireitaPouco(numero vel) {
	Motor("l", vel)
	Motor("r", 0)
	retornar (2)
}
funcao numero moveEsquerdaMuito(numero vel) {
	Motor("l", 0-vel)
	Motor("r", vel)
	retornar (3)
}
funcao numero moveDireitaMuito(numero vel) {
	Motor("l", vel)
	Motor("r", 0-vel)
	retornar (4)
}
funcao numero moveRe(numero vel) {
	Motor("l", 0-vel)
	Motor("r", 0-vel)
	retornar (5)
}
funcao numero paraCarro() {
	Motor("l", 0)
	Motor("r", 0)
	retornar (6)
}
inicio
	TravarMotor("l", falso)
	TravarMotor("r", falso)
	#AbrirConsole()
	numero contador = 0
	numero ultimoMov = 0
	enquanto (verdadeiro) farei {
		se (Cor("S2") == "Preto" e Cor("S3") == "Preto") entao {
			LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
			ultimoMov = moveFrente(200) # Ir pra frente = 0
			Esperar(200)
			DesligarLuz("led") # Ligar o LED Azul
		} senao
		se (Cor("S1") == "Preto" e Cor("S4") == "Preto") entao {
			LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
			ultimoMov = moveRe(200) # Dar ré = 5
			Esperar(200)
		} senao
		se (Cor("S1") == "Preto") entao {
			ultimoMov = moveEsquerdaMuito(200) # Gira eixo esquerda = 3
		} senao
		se (Cor("S4") == "Preto") entao {
			ultimoMov = moveDireitaMuito(200) # Gira eixo direita = 4
		} senao
		se (Cor("S2") == "Preto") entao {
			ultimoMov = moveEsquerdaPouco(200) # Curva leve esquerda = 1
		} senao
		se (Cor("S3") == "Preto") entao {
			ultimoMov = moveDireitaPouco(200) # Curva leve direita = 2
		}
		se (Cor("S1")=="Branco" e Cor("S2")=="Branco" e Cor("S3")=="Branco" e Cor("S4")=="Branco") entao {
			LigarLuz("led", 255, 255, 255) # Ligar o LED Branco
			se (ultimoMov == 0) entao {
				ultimoMov = moveFrente(100)
			}
			contador = contador + 1
			se (contador > 30) entao { # Se está a pouco tempo sem ver a linha
				LigarLuz("led", 0, 255, 0) # Ligar o LED Verde
				ultimoMov = moveFrente(100) # Frente = 0
			} senao
			se (contador > 70) entao { # Se está a muito tempo sem ver a linha
				LigarLuz("led", 255, 255, 0) # Ligar o LED Amarelo
				ultimoMov = paraCarro() # Parar Carro = 6
				# Ou dá Ré, enfim, acho que ele perdeu a linha =/
			}
		} senao {
			DesligarLuz("led")
			contador = 0
		}
		Esperar(10)
	}
fim