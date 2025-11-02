#include <iostream>
#include <string>


    struct Menu{
        std::string Food;
        int Food_price;
        std::string Drink;
        int Drink_price;
        std::string Side;
        int Side_price;
    };

int main () {
    std::string Food[] = {"Pollos Combos", "Twister Burrito", "Chicken Sandwich", "Boneless Wings"};
    int Food_price[] = {370, 240, 370, 350};
    std::string Drink[] = {"Soda", "Iced Tea", "Coffee"};
    int Drink_price[] = {120, 120, 180};
    std::string Side[] = {"Fries", "Coleslaw", "Mashed Potatoes"};
    int Side_price[] = {100, 80, 90};

    Menu comboSet1 = {"Pollos Combos", 370, "Soda", 120, "Fries", 100};
    Menu comboSet2 = {"Twister Burrito", 240 ,"Coffee", 180 ,"Coleslaw", 80};
    Menu comboSet3 = {"Chicken Sandwich", 370,  "Iced Tea", 120, "Mashed Potatoes", 90};
    Menu comboSet4 = {"Boneless Wings", 350, "Iced Tea", 120, "Fries", 100 };
    Menu comboSet5 = {"Pollos Combos", 370, "Coffee", 180, "Coleslaw", 80};




    std::cout << "---------Los Pigeon Hermanos Menu--------------" << std::endl;

    std::cout << "Combo Set 1" << std::endl;
    std::cout << "(" << comboSet1.Food << " + " << comboSet1.Drink << " + " << comboSet1.Side << ")" << std::endl;
    std::cout << comboSet1.Food_price + comboSet1.Side_price + comboSet1.Drink_price<< "?" << std::endl;
    std::cout << std::endl;

    std::cout << "Combo Set 2" << std::endl;
    std::cout << "(" << comboSet2.Food << " + " << comboSet2.Drink << " + " << comboSet2.Side << ")" << std::endl;
    std::cout << comboSet2.Food_price + comboSet2.Side_price + comboSet2.Drink_price<< "?"<< std::endl;
    std::cout << std::endl;

    std::cout << "Combo Set 3" << std::endl;
    std::cout << "(" << comboSet3.Food << " + " << comboSet3.Drink << " + " << comboSet3.Side << ")" << std::endl;
    std::cout << comboSet3.Food_price + comboSet3.Side_price + comboSet3.Drink_price<< "?" << std::endl;
    std::cout << std::endl;

    std::cout << "Combo Set 4" << std::endl;
    std::cout << "(" <<comboSet4.Food << " + " << comboSet4.Drink << " + " << comboSet4.Side << ")"<< std::endl;
    std::cout << comboSet4.Food_price + comboSet4.Side_price + comboSet4.Drink_price<< "?"<< std::endl;
    std::cout << std::endl;

    std::cout << "Combo Set 5" << std::endl;
    std::cout << "(" << comboSet5.Food << " + " << comboSet5.Drink << " + " << comboSet5.Side << ")" << std::endl;
    std::cout << comboSet5.Food_price + comboSet5.Side_price + comboSet5.Drink_price<< "" << std::endl;
    std::cout << std::endl;







     //Calc prices
    //std::cout << comboSet1.Food_price + comboSet1.Sideprice + comboSet1.Drinkprice<< std::endl;



    return 0;
}


