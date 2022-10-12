#ifndef MONEY_HPP
#define MONEY_HPP

class Money {
    private:
    long int amount {0};
    public:
    constexpr explicit Money(int amount_) : amount(amount_) {};
    constexpr auto get_money() const  {return amount;};
    constexpr Money operator+(const Money& rhs){
        return Money(amount + rhs.get_money());
    }
    constexpr Money operator-(const Money& rhs){
        if(rhs.get_money() < 0)
            return Money(amount + rhs.get_money());
        return Money(amount - rhs.get_money());
    }
    constexpr Money operator*(const Money& rhs){
        if(amount < 0 && rhs.get_money() < 0)
            return Money(-(amount * rhs.get_money()));
        return Money(amount * rhs.get_money());
    }
    constexpr Money operator"" _USD(long int amount_){
        return Money(amount_);
    }
};

#endif