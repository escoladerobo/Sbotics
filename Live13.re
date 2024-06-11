funcao numero moveFrente(numero vel) {
	Motor("l", vel)
	Motor("r", vel)
	retornar (0)
}
funcao numero moveEsquerdaPouco(numero vel) {
	Motor("l", 0-50)
	Motor("r", vel)
	retornar (1)
}
funcao numero moveDireitaPouco(numero vel) {
	Motor("l", vel)
	Motor("r", 0-50)
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
	numero ultimoMov = 0
#  Destrava Motores
	TravarMotor("l", falso)
	TravarMotor("r", falso)
# Liga motores na velocidade 200
	ultimoMov = moveFrente(200)

	numero contador = 0
	enquanto (verdadeiro) farei {
		se ( Ultrassonico("us") < 2.5 e Ultrassonico ("us") >= 0) entao {
			# Identifica obstaculo
			# Desviar de obstaculo
			ultimoMov = moveDireitaMuito(200)	# 1 - Espera ele virar a direita
			Esperar(2100)
			ultimoMov = moveFrente(200)			# 2 - Vai para Frente
			Esperar(2000)
			ultimoMov = moveEsquerdaMuito(200) # 3 - Virar 90 graus a esquerda
			Esperar(1900)
			ultimoMov = moveFrente(200)			# 4 e 5 - Vai pra Frente
			Esperar(4000)
			ultimoMov = moveEsquerdaMuito(200)	# 6 - Vira 90 graus a esquerda
			Esperar(1700)
			ultimoMov = moveFrente(200)			# 7 - Vai para Frente
			Esperar(1000)
			enquanto (Cor("sr") != "Preto") farei {
				Esperar(100)
			}
			ultimoMov = moveDireitaMuito(200)	# 8 - Vira 90 graus a direita
			Esperar(1000)
		} senao {
			se (CorVerde("sl") > (CorVermelho("sl")+CorAzul("sl"))*0.6) entao {
				ultimoMov = moveFrente(100)
				Esperar(300)
				ultimoMov = moveEsquerdaPouco(200)
				Esperar(3000)
			}
			se (CorVerde("sr") > (CorVermelho("sr")+CorAzul("sr"))*0.6) entao {
				ultimoMov = moveFrente(100)
				Esperar(300)
				ultimoMov = moveDireitaPouco(200)
				Esperar(3000)
			}
			numero diferenca = Luminosidade("sl") - Luminosidade("sr")
			se (ultimoMov == 5) entao { # Se ele perdeu a linha
				se (Cor("sl") == "Preto") entao {
					LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
					ultimoMov = moveDireitaMuito(150) # Curva leve esquerda = 1
				} senao
				se (Cor("sr") == "Preto") entao {
					LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
					ultimoMov = moveEsquerdaMuito(150) # Curva leve direita = 2
				}
			} senao
			se (Cor("sl") == "Preto" e Cor("sr") == "Preto") entao {
				LigarLuz("led", 0, 0, 0) # Ligar o LED Preto
				ultimoMov = moveFrente(100) # Ir pra frente = 0
				Esperar(100)
				DesligarLuz("led") # Ligar o LED Azul
			} senao
			se (Cor("sl") == "Preto") entao {
				se (Cor("sc") == "Preto" ) entao {
					LigarLuz("led", 128, 0, 0) # Ligar o LED Vermelho
					ultimoMov = moveEsquerdaMuito(150) # Curva esquerda = 1
				} senao {
					LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
					ultimoMov = moveEsquerdaPouco(150) #Curva leve esquerda = 1
				}
			} senao
			se (Cor("sr") == "Preto") entao {
				se (Cor("sc") == "Preto" ) entao {
					LigarLuz("led", 0, 0, 128) # Ligar o LED Azul
					ultimoMov = moveDireitaMuito(250) # Curva leve direita = 2
				} senao {
					LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
					ultimoMov = moveDireitaPouco(250) # Curva leve direita = 2
				}
			} senao
			se (Cor("sc") == "Preto") entao {
				LigarLuz("led", 0, 255, 0) # Ligar o LED Verde
				# Controle Proporcional
				Motor("l", 100 + diferenca)
				Motor("r", 100 - diferenca)
				ultimoMov = 0
				contador = 0
			}
			se (Cor("sl")=="Branco" e Cor("sc")=="Branco" e Cor("sr")=="Branco") entao { # Provavelmente eu perdi a linha
				DesligarLuz("led")
				se (ultimoMov == 0) entao {
					# Controle Proporcional
					Motor("l", 100 + diferenca)
					Motor("r", 100 - diferenca)
					ultimoMov = 0
					se (Luminosidade("sc") < 140) entao {
						contador = 0
					}
				} senao
				se (ultimoMov == 1) entao { # Fazia curva à esquerda
					ultimoMov = moveEsquerdaMuito(100)
				} senao
				se (ultimoMov == 2) entao { # Fazia curva à direita
					ultimoMov = moveDireitaMuito(100)
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
			Esperar(5)
		}
	}

fim