int	my_isalpha(int smbl)
{
	if ((smbl >= 65 && smbl <= 90) || (smbl >= 97 && smbl <= 122))
		return (1);
	else
		return (0);
}
