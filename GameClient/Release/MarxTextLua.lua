-- C++ ���� ����� �Լ��� ȣ���Ѵ�.
-- �Ϲ����� lua �Լ��� �����Ѵ�.

-- ���� ����.
function OnCreate(arg1, arg2)
	return arg1 + arg2
end

-- 
function LuaTestSubject(ObjName)
  MarxObject2:is_test(ObjName);
  return 10;
end



duration = 0;
revers = true;
speed = 0.02;

function frameMove(elapsedtime)

  if( MarxObject4 ~= nil) then
  	if(revers == true) then
		MarxObject4:setTranslate(0,speed*-1,0);
	elseif( revers == false) then
		MarxObject4:setTranslate(0,speed,0);
	end
	
	duration = duration + speed;
	
	if(duration > 0.20) then
		if(revers == false) then
			revers = true;
		elseif(revers == true) then
			revers = false;
		end
		duration =0;
	end
	
  end
  
  return 10;
end

