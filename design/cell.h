#pragma once

#include "common.h"
#include "formula.h"

#include <optional>
#include <set>
#include <unordered_set>

class Cell : public CellInterface {
public:
    explicit Cell(SheetInterface& sheet);
    ~Cell();

    Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;

    void Set(std::string text);
    void Clear();

    void InvalidateCache(); // сбрасывает кэш а так же сбрасывает и у всех зависимых ячеек

    std::set<Cell*> dependents_; //Обратныйе рёбра
    // В случае если значение этой ячейки поменялось надо поменять и все те ячейки которые зависят от этой

private:
    std::unique_ptr<FormulaInterface> formula_;
    std::string text_;
    // Храним вычесленное значение
    std::optional<Value> cache_;
    // Сылка на таблицу от куда будут браться ячейки
    SheetInterface& sheet_;
};
