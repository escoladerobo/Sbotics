inicio
	TravarMotor("l", falso)
	TravarMotor("r", falso)
	#AbrirConsole()
	numero contador = 0
	enquanto (verdadeiro) farei {
		se (Cor("S2") == "Preto" e Cor("S3") == "Preto") entao {
			#EscreverLinha("Cruzamento")
			Motor("l", 100)
			Motor("r", 100)
		} senao
		se (Cor("S2") == "Preto") entao {
			#EscreverLinha("Fita! Esquerda")
			Motor("l", 0)
			Motor("r", 200)
		} senao
		se (Cor("S3") == "Preto") entao {
			#EscreverLinha("Fita! Direita")
			Motor("l", 200)
			Motor("r", 0)
		} senao
		se (Cor("S1") == "Preto") entao {
			#EscreverLinha("Fita! Esquerda Muito")
			Motor("l", 0-200)
			Motor("r", 200)
		} senao
		se (Cor("S4") == "Preto") entao {
			#EscreverLinha("Fita! Direita Muito")
			Motor("l", 200)
			Motor("r", 0-200)
		} senao {
			#EscreverLinha("Frente")
			Motor("l", 100)
			Motor("r", 100)
		}
		se (Cor("S1")=="Branco" e Cor("S2")=="Branco" e Cor("S3")=="Branco" e Cor("S4")=="Branco") entao {
			#EscreverLinha("Tudo Branco!")
			contador = contador + 1
			#EscreverLinha(VirarTexto(contador))
		} senao {
			contador = 0
		}
		Esperar(20)
	}
fim