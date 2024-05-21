inicio
	Escrever("live7")
	TravarMotor("l", falso)
	TravarMotor("r", falso)
	Motor("l", 100)
	Motor("r", 100)
	Escrever( VirarTexto( Ultrassonico("us") ) )
fim