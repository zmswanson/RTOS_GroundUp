void delay(int time) {
	int volatile delay = 0;
	while((delay++) < time);
}