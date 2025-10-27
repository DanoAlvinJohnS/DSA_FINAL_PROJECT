#include <iostream>
#include <string>


    struct Menu{
        std::string food;
        int Foodprice;
        std::string drink;
        int Drinkprice;
        std::string Side;
        int Sideprice;
    };

int main () {
    std::string Food[] = {"Pollos Combos", "Twister Burrito", "Chicken Sandwich", "Boneless Wings"};
    int Foodprice[] = {370, 240, 370, 350};
    std::string Drink[] = {"Soda", "Iced Tea", "Coffee"};
    int Drinkprice[] = {120, 120, 180};
    std::string Side[] = {"Fries", "Coleslaw", "Mashed Potatoes"};
    int Sideprice[] = {100, 80, 90};

    Menu comboSet1 = {"Pollos Combos", 370, "Soda", 120, "Fries", 100};
    Menu comboSet2 = {"Twister Burrito", 240 ,"Coffee", 180 ,"Coleslaw", 80};
    Menu comboSet3 = {"Chicken Sandwich", 370,  "Iced Tea", 120, "Mashed Potatoes", 90};
    Menu comboSet4 = {"Boneless Wings", 350, "Iced Tea", 120, "Fries", 100 };
    Menu comboSet5 = {"Pollos Combos", 370, "Boneless Wings", 350, "Coleslaw", 80 "Soda", 120};




    std::cout << "---------Los ???????? ???? Ordering System--------------" << std::endl;

    std::cout << "Menu" << std::endl;
    std::cout << comboSet1.Food << " + " << comboSet1.Drink << " + " << comboSet1.Side << std::endl;










     #Calc prices
    std::cout << comboSet1.Foodprice + comboSet1.Sideprice + comboSet1.Drinkprice<< std::endl;



    return 0;
}


