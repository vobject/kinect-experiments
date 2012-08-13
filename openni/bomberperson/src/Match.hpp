#ifndef MATCH_HPP
#define MATCH_HPP

#include <memory>
#include <tuple>
#include <vector>

class Field;
class Player;
class Cell;
class SceneObject;

class Match
{
public:
   Match(const std::shared_ptr<Field>& playing_field,
         const std::vector<std::shared_ptr<Player>>& players);
   virtual ~Match();

   Match(const Match&) = delete;
   Match& operator=(const Match&) = delete;

   void Update(int elapsed_time);

   std::shared_ptr<Field> GetField() const;
   std::vector<std::shared_ptr<Player>> GetPlayers() const;

private:
   std::shared_ptr<Cell> GetCellFromObject(const std::shared_ptr<SceneObject>& obj) const;

   std::shared_ptr<Field> mField;
   std::vector<std::shared_ptr<Player>> mPlayers;
};

#endif // MATCH_HPP
