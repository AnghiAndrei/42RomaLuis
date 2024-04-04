void PhoneBook::PhoneBook(){
    insert=0;
    list[0]=NULL;
    list[1]=NULL;
    list[2]=NULL;
    list[3]=NULL;
    list[4]=NULL;
    list[5]=NULL;
    list[6]=NULL;
    list[7]=NULL;
    list[8]=NULL;
}

void PhoneBook::add_contact(Contact cont)
{
    if (insert==9)
        insert=0;
    list[insert]=cont;
    insert++;
}

void PhoneBook::search(){
    int i=0, i2=0;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "|    index |firstname | lastname | surname  |" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    while(i != 8){
        std::cout<<i<<"|         | ";
        i2=0;
        while (list[insert].name[i2] != '\0' && i2 != 10)
        {
            if(i2 == 10 && list[insert].name[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<list[insert].name[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"| ";
        i2=0;
        while (list[insert].name2[i2] != '\0' && i2 != 10)
        {
            if(i2 == 10 && list[insert].name2[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<list[insert].name2[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"| ";
        i2=0;
        while (list[insert].surname[i2] != '\0' && i2 != 10)
        {
            if(i2 == 10 && list[insert].surname[i2+1] != '\0')
                std::cout<<".";
            else
                std::cout<<list[insert].surname[i2];
            i2++;
        }
        while (i2 != 10)
        {
            std::cout<<" ";
            i2++;
        }
        std::cout<<"|\n";
        i++;
    }
    do{
        std::cout<<"SEARCH>";
        std::cin>>i;
    }while (!(i > 0 && i < 8) && list[i] != NULL);
    std::cout<<"Index: "<<i<<"\nFirst name: "<<list[insert].name<<"\nLast name: "<<list[insert].name2<<"\nSurname: "<<list[insert].surname<<"\nPhone: "<<list[insert].tel<<"\nDarkest secret: "<<list[insert].dse;
}