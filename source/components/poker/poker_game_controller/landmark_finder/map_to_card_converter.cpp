#include "components/poker/poker_game_controller/landmark_finder/map_to_card_converter.h"

namespace poker {

Card MapToCardConverter::Convert(int x_location, int y_location) const {
    Card card;
    if(x_location < 400) {
        card.suit = Suit::SUIT_HEART;
    }
    if(x_location < 300) {
        card.suit = Suit::SUIT_DIAMOND;
    }
    if(x_location < 200) {
        card.suit = Suit::SUIT_CLUBS;
    }
    if(x_location < 100) {
        card.suit = Suit::SUIT_SPADES;
    }

    if(y_location < 100) {
        card.card_value =  CardValue::CARD_VALUE_ACE;
        return card;
    }
    if(y_location < 200) {
        card.card_value =  CardValue::CARD_VALUE_TWO;
        return card;
    }
    if(y_location < 300) {
        card.card_value =  CardValue::CARD_VALUE_THREE;
        return card;
    }
    if(y_location < 400) {
        card.card_value =  CardValue::CARD_VALUE_FOUR;
        return card;
    }
    if(y_location < 500) {
        card.card_value =  CardValue::CARD_VALUE_FIVE;
        return card;
    }
    if(y_location < 600) {
        card.card_value =  CardValue::CARD_VALUE_SIX;
        return card;
    }
    if(y_location < 700) {
        card.card_value =  CardValue::CARD_VALUE_SEVEN;
        return card;
    }
    if(y_location < 800) {
        card.card_value =  CardValue::CARD_VALUE_EIGHT;
        return card;
    }
    if(y_location < 900) {
        card.card_value =  CardValue::CARD_VALUE_NINE;
        return card;
    }
    if(y_location < 1000) {
        card.card_value =  CardValue::CARD_VALUE_TEN;
        return card;
    }
    if(y_location < 1100) {
        card.card_value =  CardValue::CARD_VALUE_JACK;
        return card;
    }
    if(y_location < 1200) {
        card.card_value =  CardValue::CARD_VALUE_QUEEN;
        return card;
    }
    if(y_location < 1300) {
        card.card_value =  CardValue::CARD_VALUE_KING;
        return card;
    }
    return card;
}

}  // namespace poker
