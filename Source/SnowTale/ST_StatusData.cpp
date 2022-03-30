
#include "ST_StatusData.h"

FST_Status::FST_Status()
	: HP(0.0f)
	, ATK(0.0f)
	, AttackSpeed(0.0f)
	, DEF(0.0f)
	, MoveSpeed(0.0f)
	, Range(0.0f) {}

FST_Status& FST_Status::operator=(const FST_Status& StatusParam)
{
	HP = StatusParam.HP;
	ATK = StatusParam.ATK;
	AttackSpeed = StatusParam.AttackSpeed;
	DEF = StatusParam.DEF;
	MoveSpeed = StatusParam.MoveSpeed;
	Range = StatusParam.Range;

	return *this;
}

FST_Status FST_Status::operator+(const FST_Status& StatusParam) const
{
	FST_Status Status = StatusParam;

	Status.HP += HP;
	Status.ATK += ATK;
	Status.AttackSpeed += AttackSpeed;
	Status.DEF += DEF;
	Status.MoveSpeed += MoveSpeed;
	Status.Range += Range;

	return Status;
}

FST_Status FST_Status::operator-(const FST_Status& StatusParam) const
{
	FST_Status Status = StatusParam;

	Status.HP -= HP;
	Status.ATK -= ATK;
	Status.AttackSpeed -= AttackSpeed;
	Status.DEF -= DEF;
	Status.MoveSpeed -= MoveSpeed;
	Status.Range -= Range;

	return Status;
}

FST_Status FST_Status::operator*(float Ratio) const
{
	FST_Status Status = *this;

	Status.HP = HP * Ratio;
	Status.ATK = ATK * Ratio;
	Status.AttackSpeed = AttackSpeed * Ratio;
	Status.DEF = DEF * Ratio;
	Status.MoveSpeed = MoveSpeed * Ratio;
	Status.Range = Range * Ratio;

	return Status;
}

FST_Status FST_Status::operator/(float Ratio) const
{
	FST_Status Status = *this;

	Status.HP = HP / Ratio;
	Status.ATK = ATK / Ratio;
	Status.AttackSpeed = AttackSpeed / Ratio;
	Status.DEF = DEF / Ratio;
	Status.MoveSpeed = MoveSpeed / Ratio;
	Status.Range = Range * Ratio;

	return Status;
}

FST_Status& FST_Status::operator+=(const FST_Status& StatusParam)
{
	*this = *this + StatusParam;
	return *this;
}

FST_Status& FST_Status::operator-=(const FST_Status& StatusParam)
{
	*this = *this - StatusParam;
	return *this;
}

FST_Status& FST_Status::operator*=(float Ratio)
{
	*this = *this * Ratio;
	return *this;
}

FST_Status& FST_Status::operator/=(float Ratio)
{
	*this = *this / Ratio;
	return *this;
}
