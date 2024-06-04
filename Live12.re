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
	retornar (1)
}
funcao numero moveDireitaMuito(numero vel) {
	Motor("l", vel)
	Motor("r", 0-vel)
	retornar (2)
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
		se (ultimoMov == 5) entao { # Se ele perdeu a linha
			se (Cor("sl") == "Preto") entao {
				LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
				ultimoMov = moveDireitaMuito(250) # Curva leve esquerda = 1
			} senao
			se (Cor("sr") == "Preto") entao {
				LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
				ultimoMov = moveEsquerdaMuito(250) # Curva leve direita = 2
			}
		} senao
		se (Cor("sl") == "Preto" e Cor("sr") == "Preto") entao {
			LigarLuz("led", 0, 0, 0) # Ligar o LED Preto
			ultimoMov = moveFrente(200) # Ir pra frente = 0
			Esperar(200)
			DesligarLuz("led") # Ligar o LED Azul
		} senao
		se (Cor("sl") == "Preto") entao {
			LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
			ultimoMov = moveEsquerdaPouco(250) # Curva leve esquerda = 1
		} senao
		se (Cor("sr") == "Preto") entao {
			LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
			ultimoMov = moveDireitaPouco(250) # Curva leve direita = 2
		} senao
		se (Cor("sc") == "Preto") entao {
			LigarLuz("led", 0, 255, 0) # Ligar o LED Verde
			ultimoMov = moveFrente(200)
		}
		se (Cor("sl")=="Branco" e Cor("sc")=="Branco" e Cor("sr")=="Branco") entao {
			DesligarLuz("led")
			se (ultimoMov == 0) entao {
				ultimoMov = moveFrente(100)
			} senao
			se (ultimoMov == 1) entao { # Fazia curva à esquerda
				ultimoMov = moveEsquerdaMuito(200)
			} senao
			se (ultimoMov == 2) entao { # Fazia curva à direita
				ultimoMov = moveDireitaMuito(200)
			}
			contador = contador + 1
			se (contador > 30) entao { # A pouco tempo sem ver a linha
				LigarLuz("led", 255, 255, 0) # Ligar o LED Amarelo
			}
			se (contador > 50) entao { # A muito tempo sem ver a linha
				LigarLuz("led", 255, 255, 255) # Ligar o LED Branco
				ultimoMov = moveRe(100) # Parar Carro = 6
				# Ou dá Ré, enfim, acho que ele perdeu a linha =/
			}
		} senao {
			contador = 0
		}
		Esperar(10)
	}
fim