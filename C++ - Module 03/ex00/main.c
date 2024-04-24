int main(){
    ClapTrap bot1=ClapTrap("02");
    ClapTrap bot2=ClapTrap("Origami");
    bot1.attack(bot2);
    bot2.attack(bot1);
    bot1.beRepaired(10);
}