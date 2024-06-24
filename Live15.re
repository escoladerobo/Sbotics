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
	Motor("r", vel/2)
	retornar (1)
}
funcao numero moveDireitaMuito(numero vel) {
	Motor("l", vel/2)
	Motor("r", 0-vel)
	retornar (2)
}
funcao numero moveRe(numero vel) {
	Motor("l", 0-vel)
	Motor("r", 0-vel)
	retornar (5)
}

tarefa paraCarro() {
	Motor("l", 0)
	Motor("r", 0)
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
			Esperar(2500)
			ultimoMov = moveEsquerdaMuito(200) # 3 - Virar 90 graus a esquerda
			Esperar(1800)
			ultimoMov = moveFrente(200)			# 4 e 5 - Vai pra Frente
			Esperar(4000)
			ultimoMov = moveEsquerdaMuito(200)	# 6 - Vira 90 graus a esquerda
			Esperar(1800)
			ultimoMov = moveFrente(200)			# 7 - Vai para Frente
			Esperar(2000)
			enquanto (Cor("sr") != "Preto") farei {
				Esperar(100)
			}
			ultimoMov = moveDireitaMuito(200)	# 8 - Vira 90 graus a direita
			Esperar(1000)
		} senao {
			se (CorVerde("sc") > (CorVermelho("sc")+CorAzul("sc"))*0.65) entao { # Não deveria acontecer
				TravarMotor("l", verdadeiro)
				TravarMotor("r", verdadeiro)
				Esperar(500)
				TravarMotor("l", falso)
				TravarMotor("r", falso)
				LigarLuz("led", 255, 255, 255) # Ligar o LED Branco
				ultimoMov = moveRe(100) # MoveRe = 5
				Esperar(1000)
				ultimoMov = moveDireitaMuito(200)
				Esperar(250)
			} senao
			se (CorVerde("sl") > (CorVermelho("sl")+CorAzul("sl"))*0.65) entao {
				se (ultimoMov == 5) entao {
					ultimoMov = moveDireitaPouco(100)
					contador = 0
				} senao {
					ultimoMov = moveFrente(100)
					Esperar(300)
					ultimoMov = moveEsquerdaPouco(200)
					Esperar(3000)
				}
			} senao
			se (CorVerde("sr") > (CorVermelho("sr")+CorAzul("sr"))*0.65) entao {
				se (ultimoMov == 5) entao {
					ultimoMov = moveEsquerdaPouco(100)
					contador = 0
				} senao {
					ultimoMov = moveFrente(100)
					Esperar(300)
					ultimoMov = moveDireitaPouco(200)
					Esperar(3000)
				}
			} senao
			se ((CorVermelho("sl")>(CorVerde("sl")+CorAzul("sl"))*0.65) e
				(CorVermelho("sr")>(CorVerde("sr")+CorAzul("sr"))*0.65))entao {
				paraCarro()
				ultimoMov = 6
				Esperar(100000)
			} senao {
				texto CorSl = "Branco"
				se (Luminosidade("sl") < 130) entao {
					CorSl = "Preto"
				}
				texto CorSc = "Branco"
				se (Luminosidade("sc") < 130) entao {
					CorSc = "Preto"
				}
				texto CorSr = "Branco"
				se (Luminosidade("sr") < 130) entao {
					CorSr = "Preto"
				}
				se (ultimoMov == 5) entao { # Se ele perdeu a linha
					se (CorSl == "Preto") entao {
						LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
						ultimoMov = moveDireitaMuito(150) # Curva leve esquerda = 1
						Esperar(500)
					} senao
					se (CorSr == "Preto") entao {
						LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
						ultimoMov = moveEsquerdaMuito(150) # Curva leve direita = 2
						Esperar(500)
					}
				} senao
				se (CorSl == "Preto" e CorSr == "Preto") entao {
					LigarLuz("led", 0, 0, 0) # Ligar o LED Preto
					ultimoMov = moveFrente(100) # Ir pra frente = 0
					Esperar(100)
					DesligarLuz("led") # Ligar o LED Azul
				} senao
				se (CorSl == "Preto") entao {
					se (CorSc == "Preto" ) entao { # Pode ser interseção em T
						LigarLuz("led", 128, 0, 0) # Ligar o LED Vermelho
						paraCarro()
							ultimoMov = 6
						TravarMotor("l", verdadeiro)
						TravarMotor("r", verdadeiro)
						Esperar(500)
						TravarMotor("l", falso)
						TravarMotor("r", falso)
						ultimoMov = moveFrente(100)
						Esperar(300)
						TravarMotor("l", verdadeiro)
						TravarMotor("r", verdadeiro)
						Esperar(500)
						TravarMotor("l", falso)
						TravarMotor("r", falso)
						Esperar(500)
						CorSl = "Branco"
						se (CorVerde("sl") > (CorVermelho("sl")+CorAzul("sl"))*0.65) entao {
								CorSl = "Verde"
						} senao {
								se (Luminosidade("sl") < 130) entao {
									CorSl = "Preto"
								}
								CorSc = "Branco"
								se (Luminosidade("sc") < 130) entao {
									CorSc = "Preto"
								}
								CorSr = "Branco"
								se (Luminosidade("sr") < 130) entao {
									CorSr = "Preto"
								}
								se (CorSl=="Branco" e CorSc=="Branco" e CorSr=="Branco") entao {
									ultimoMov = moveEsquerdaMuito(150) # Curva esquerda = 1
									Esperar(1200)
								}
							}
					} senao {
						LigarLuz("led", 255, 0, 0) # Ligar o LED Vermelho
						ultimoMov = moveEsquerdaPouco(150) #Curva leve esquerda = 1
					}
				} senao
				se (CorSr == "Preto") entao {
					se (CorSc == "Preto" ) entao { # Pode ser interseção em T
						LigarLuz("led", 0, 0, 128) # Ligar o LED Azul
						paraCarro()
						ultimoMov = 6
						TravarMotor("l", verdadeiro)
						TravarMotor("r", verdadeiro)
						Esperar(500)
						TravarMotor("l", falso)
						TravarMotor("r", falso)
						ultimoMov = moveFrente(100)
						Esperar(300)
						TravarMotor("l", verdadeiro)
						TravarMotor("r", verdadeiro)
						Esperar(500)
						TravarMotor("l", falso)
						TravarMotor("r", falso)
						Esperar(500)
						CorSl = "Branco"
						se (Luminosidade("sl") < 130) entao {
								CorSl = "Preto"
						}
						CorSc = "Branco"
						se (Luminosidade("sc") < 130) entao {
								CorSc = "Preto"
						}
						CorSr = "Branco"
						se (CorVerde("sr") > (CorVermelho("sr")+CorAzul("sr"))*0.65) entao {
								CorSr = "Verde"
						} senao {
								se (Luminosidade("sr") < 130) entao {
									CorSr = "Preto"
								}
								se (CorSl=="Branco" e CorSc=="Branco" e CorSr=="Branco") entao {
									ultimoMov = moveDireitaMuito(250) # Curva direita = 2
									Esperar(1200)
								}
						}
					} senao {
						LigarLuz("led", 0, 0, 255) # Ligar o LED Azul
						ultimoMov = moveDireitaPouco(250) # Curva leve direita = 2
					}
				} senao
				se (CorSc == "Preto") entao {
					numero diferenca = Luminosidade("sl") - Luminosidade("sr")
					LigarLuz("led", 0, 255, 0) # Ligar o LED Verde
					# Controle Proporcional
					Motor("l", 100 + diferenca)
					Motor("r", 100 - diferenca)
					ultimoMov = 0
					contador = 0
				}
				se (CorSl=="Branco" e CorSc=="Branco" e CorSr=="Branco") entao {
					DesligarLuz("led")
					numero diferenca2 = Luminosidade("sl") - Luminosidade("sr")
					se (ultimoMov == 0 ou ultimoMov == 5) entao {
						# Controle Proporcional
						Motor("l", 100 + diferenca2)
						Motor("r", 100 - diferenca2)
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
						ultimoMov = moveRe(100) # MoveRe = 5
						# Ou dá Ré, enfim, acho que ele perdeu a linha =/
					}
				} senao {
					contador = 0
				}
			}
			Esperar(5)
		}
	}
fim