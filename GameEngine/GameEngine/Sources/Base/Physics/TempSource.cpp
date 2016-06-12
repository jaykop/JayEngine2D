////		1st case
////    |----------||----------|
////    |		     ||		     |
////    |   spt1	 ||   spt2   |
////    |		     ||		     |
////    |----------||----------|
////
//if (spt1->GetPosition().x < spt2->GetPosition().x)
//{
//	vec3 diff = (spt2->GetPosition() - spt1->GetPosition()).Absolute();

//	//		1-1st case
//	//    |----------|
//	//    |		     ||----------|
//	//    |   spt1	 ||		     |
//	//    |		     ||   spt2   |
//	//    |----------||		     |
//	//				  |----------|
//	if (diff.x > diff.y)
//	{
//		spt1->SetPosition(vec3(spt2->GetPosition().x - spt2->GetScale().x / 2 - spt1->GetScale().x / 2,
//			spt1->GetPosition().y, spt1->GetPosition().z));

//		spt2->SetPosition(vec3(spt1->GetPosition().x + spt1->GetScale().x / 2 + spt2->GetScale().x / 2,
//			spt2->GetPosition().y, spt2->GetPosition().z));
//	}

//	//		1-1-1st case					1-1-2nd case
//	//    |----------|					|----------|
//	//    |		     |					|		   |
//	//    |   spt1	 |					|   spt2   |
//	//    |		     |					|		   |
//	//    |----------|					|----------|
//	//			|----------|	|----------|
//	//			|		   |	|		   |
//	//			|   spt2   |	|   spt1   |
//	//			|		   |	|		   |
//	//			|----------|	|----------|
//	//
//	else
//	{
//		// 1-1-1st case
//		if (spt1->GetPosition().y > spt2->GetPosition().y)
//		{
//			spt1->SetPosition(vec3(spt1->GetPosition().x,
//				spt2->GetPosition().y + spt2->GetScale().y / 2 + spt1->GetScale().y / 2,
//				spt1->GetPosition().z));

//			spt2->SetPosition(vec3(spt2->GetPosition().x,
//				spt1->GetPosition().y - spt1->GetScale().y / 2 - spt2->GetScale().y / 2,
//				spt2->GetPosition().z));
//		}

//		// 1-1-2nd case
//		else
//		{
//			spt1->SetPosition(vec3(spt1->GetPosition().x,
//				spt2->GetPosition().y - spt2->GetScale().y / 2 - spt1->GetScale().y / 2,
//				spt1->GetPosition().z));

//			spt2->SetPosition(vec3(spt2->GetPosition().x,
//				spt1->GetPosition().y + spt1->GetScale().y / 2 + spt2->GetScale().y / 2,
//				spt2->GetPosition().z));
//		}
//	}
//}

////		2nd case
////    |----------||----------|
////    |		     ||		     |
////    |   spt2	 ||   spt1   |
////    |		     ||		     |
////    |----------||----------|
////
//else
//{
//	vec3 diff = (spt1->GetPosition() - spt2->GetPosition()).Absolute();

//	//		2-1st case
//	//    |----------|
//	//    |		     ||----------|
//	//    |   spt2	 ||		     |
//	//    |		     ||   spt1   |
//	//    |----------||		     |
//	//				  |----------|
//	if (diff.x > diff.y)
//	{
//		spt1->SetPosition(vec3(spt2->GetPosition().x + spt2->GetScale().x / 2 + spt1->GetScale().x / 2,
//			spt1->GetPosition().y, spt1->GetPosition().z));

//		spt2->SetPosition(vec3(spt1->GetPosition().x - spt1->GetScale().x / 2 - spt2->GetScale().x / 2,
//			spt2->GetPosition().y, spt2->GetPosition().z));
//	}

//	//		2-1-1st case					2-1-2nd case
//	//    |----------|					|----------|
//	//    |		     |					|		   |
//	//    |   spt2	 |					|   spt1   |
//	//    |		     |					|		   |
//	//    |----------|					|----------|
//	//			|----------|	|----------|
//	//			|		   |	|		   |
//	//			|   spt1   |	|   spt2   |
//	//			|		   |	|		   |
//	//			|----------|	|----------|
//	//
//	else
//	{
//		// 2-1-1st case
//		if (spt1->GetPosition().y < spt2->GetPosition().y)
//		{
//			spt1->SetPosition(vec3(spt1->GetPosition().x,
//				spt2->GetPosition().y - spt2->GetScale().y / 2 - spt1->GetScale().y / 2,
//				spt1->GetPosition().z));

//			spt2->SetPosition(vec3(spt2->GetPosition().x,
//				spt1->GetPosition().y + spt1->GetScale().y / 2 + spt2->GetScale().y / 2,
//				spt2->GetPosition().z));
//		}

//		// 2-1-2nd case
//		else
//		{
//			spt1->SetPosition(vec3(spt1->GetPosition().x,
//				spt2->GetPosition().y + spt2->GetScale().y / 2 + spt1->GetScale().y / 2,
//				spt1->GetPosition().z));

//			spt2->SetPosition(vec3(spt2->GetPosition().x,
//				spt1->GetPosition().y - spt1->GetScale().y / 2 - spt2->GetScale().y / 2,
//				spt2->GetPosition().z));
//		}
//	}
//}