int main() {
	int i = 5;
	while (i > 1)  {
		if (i==4) {
			break;
		}
		if (i<4) {
			return 9;
		}
		i = i - 1;
	}
	return 5;
}
