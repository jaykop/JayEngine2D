//		1st case
//    |----------||----------|
//    |		     ||		     |
//    |   spt1	 ||   spt2   |
//    |		     ||		     |
//    |----------||----------|
//
if (spt1->GetPosition().x < spt2->GetPosition().x)
{
	vec3 diff = (spt2->GetPosition() - spt1->GetPosition()).Absolute();

	//		1-1st case
	//    |----------|
	//    |		     ||----------|
	//    |   spt1	 ||		     |
	//    |		     ||   spt2   |
	//    |----------||		     |
	//				  |----------|
	if (diff.x > diff.y)
	{
		spt1->SetPosition(vec3(spt2->GetPosition().x - spt2->GetScale().x / 2 - spt1->GetScale().x / 2,
			spt1->GetPosition().y, spt1->GetPosition().z));

		spt2->SetPosition(vec3(spt1->GetPosition().x + spt1->GetScale().x / 2 + spt2->GetScale().x / 2,
			spt2->GetPosition().y, spt2->GetPosition().z));
	}

	//		1-1-1st case					1-1-2nd case
	//    |----------|					|----------|
	//    |		     |					|		   |
	//    |   spt1	 |					|   spt2   |
	//    |		     |					|		   |
	//    |----------|					|----------|
	//			|----------|	|----------|
	//			|		   |	|		   |
	//			|   spt2   |	|   spt1   |
	//			|		   |	|		   |
	//			|----------|	|----------|
	//
	else
	{
		// 1-1-1st case
		if (spt1->GetPosition().y > spt2->GetPosition().y)
		{
			spt1->SetPosition(vec3(spt1->GetPosition().x,
				spt2->GetPosition().y + spt2->GetScale().y / 2 + spt1->GetScale().y / 2,
				spt1->GetPosition().z));

			spt2->SetPosition(vec3(spt2->GetPosition().x,
				spt1->GetPosition().y - spt1->GetScale().y / 2 - spt2->GetScale().y / 2,
				spt2->GetPosition().z));
		}

		// 1-1-2nd case
		else
		{
			spt1->SetPosition(vec3(spt1->GetPosition().x,
				spt2->GetPosition().y - spt2->GetScale().y / 2 - spt1->GetScale().y / 2,
				spt1->GetPosition().z));

			spt2->SetPosition(vec3(spt2->GetPosition().x,
				spt1->GetPosition().y + spt1->GetScale().y / 2 + spt2->GetScale().y / 2,
				spt2->GetPosition().z));
		}
	}
}

//		2nd case
//    |----------||----------|
//    |		     ||		     |
//    |   spt2	 ||   spt1   |
//    |		     ||		     |
//    |----------||----------|
//
else
{
	vec3 diff = (spt1->GetPosition() - spt2->GetPosition()).Absolute();

	//		2-1st case
	//    |----------|
	//    |		     ||----------|
	//    |   spt2	 ||		     |
	//    |		     ||   spt1   |
	//    |----------||		     |
	//				  |----------|
	if (diff.x > diff.y)
	{
		spt1->SetPosition(vec3(spt2->GetPosition().x + spt2->GetScale().x / 2 + spt1->GetScale().x / 2,
			spt1->GetPosition().y, spt1->GetPosition().z));

		spt2->SetPosition(vec3(spt1->GetPosition().x - spt1->GetScale().x / 2 - spt2->GetScale().x / 2,
			spt2->GetPosition().y, spt2->GetPosition().z));
	}

	//		2-1-1st case					2-1-2nd case
	//    |----------|					|----------|
	//    |		     |					|		   |
	//    |   spt2	 |					|   spt1   |
	//    |		     |					|		   |
	//    |----------|					|----------|
	//			|----------|	|----------|
	//			|		   |	|		   |
	//			|   spt1   |	|   spt2   |
	//			|		   |	|		   |
	//			|----------|	|----------|
	//
	else
	{
		// 2-1-1st case
		if (spt1->GetPosition().y < spt2->GetPosition().y)
		{
			spt1->SetPosition(vec3(spt1->GetPosition().x,
				spt2->GetPosition().y - spt2->GetScale().y / 2 - spt1->GetScale().y / 2,
				spt1->GetPosition().z));

			spt2->SetPosition(vec3(spt2->GetPosition().x,
				spt1->GetPosition().y + spt1->GetScale().y / 2 + spt2->GetScale().y / 2,
				spt2->GetPosition().z));
		}

		// 2-1-2nd case
		else
		{
			spt1->SetPosition(vec3(spt1->GetPosition().x,
				spt2->GetPosition().y + spt2->GetScale().y / 2 + spt1->GetScale().y / 2,
				spt1->GetPosition().z));

			spt2->SetPosition(vec3(spt2->GetPosition().x,
				spt1->GetPosition().y - spt1->GetScale().y / 2 - spt2->GetScale().y / 2,
				spt2->GetPosition().z));
		}
	}
}

// Reflect 1st sprite
// Get 1st body's edges 
Vertices body2 = GetVertices(spt2);
vec3 body2edge_start, body2edge_end;
for (int i = 0; i < 4; ++i)
{
	if (i == 3)
	{
		body2edge_start = body2[i];
		body2edge_end = body2[0];
	}

	else
	{
		body2edge_start = body2[i];
		body2edge_end = body2[i + 1];
	}

	// Get collided edge
	//if (Get2ndBoxEdge(body2edge_start, body2edge_end, spt1))
	//break;
}

vec3 edge_norm = (body2edge_end - body2edge_start).Rotation(90.f);
vec3 new_Velocity = spt1->GetRigidBody()->GetVelocity().Reflection(edge_norm);

//This is line - OBB collision method
float greatest_tmin = 0, smallest_tmax = 100000.f;
Vertices body1 = GetVertices(sprite1);
//Get 2nd body's edges 
for (int j = 0; j < 4; ++j)
{
	vec3 body1edge_start, body1edge_end;
	if (j == 3)
	{
		body1edge_start = body1[j];
		body1edge_end = body1[0];
	}

	else
	{
		body1edge_start = body1[j];
		body1edge_end = body1[j + 1];
	}

	Math::boolVec output = Math::IntersectOf2Lines(body1edge_start, body1edge_end,
		body2edge_start, body2edge_end);

	//Assign proper valuse
	if (output.boolean)
	{
		if (tx_Toggle)
		{
			tx_min = tx_max = output.vector.x;
			ty_min = ty_max = output.vector.y;
			tx_Toggle = false;
		}

		if (output.vector.x > tx_max) tx_max = output.vector.x;
		if (output.vector.x < tx_min) tx_min = output.vector.x;
		if (output.vector.y > ty_max) ty_max = output.vector.y;
		if (output.vector.y < ty_min) ty_min = output.vector.y;
	}
}

if (tx_max > ty_max) smallest_tmax = ty_max;
else smallest_tmax = tx_max;

if (tx_min < ty_min) greatest_tmin = ty_min;
else greatest_tmin = tx_min;

if (greatest_tmin > smallest_tmax)
return false;

return true;