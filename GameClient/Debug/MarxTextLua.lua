-- C++ 에서 등록한 함수를 호출한다.
-- 일반적인 lua 함수를 선언한다.
-- 최초 제작.

-- 기본 키세팅 로드
loadfile("OpenGLLuakeysetting.lua");

function OnCreate(arg1, arg2)
	return arg1 + arg2
end

-- 
function LuaTestSubject(ObjName)
	if(MainCharacter~= nil) then
		--MainCharacter:setRotate(45,45,0)
	end
  return 10;
end



duration = 0;
revers = true;
speed = 0.02;

-- 0 위 1 오른쪽 2 아래 3왼쪽
KeyDownValue = { 0,0,0,0 };
-- 0 안누룸 1 누름

function frameMove(elapsedtime)

	local rotation = 0;
	local keydowning = false;
	
	if(KeyDownValue[1] == 1)then
		MainCharacter:setTranslate(0,0.1,0);
		rotation = 270;
		keydowning = true;
	end
	if(KeyDownValue[2] == 1)then
		MainCharacter:setTranslate(0,-0.1,0);
		rotation = 90;
		keydowning = true;
	end
	if(KeyDownValue[3] == 1)then
		MainCharacter:setTranslate(-0.1,0,0);
		rotation = 360;
		keydowning = true;
	end
	if(KeyDownValue[4] == 1)then
		MainCharacter:setTranslate(0.1,0,0);
		rotation = 180;
		keydowning = true;
	end
	
	if(KeyDownValue[1] == 1 and KeyDownValue[4] == 1)then
		rotation = 225;
	end
	
	if(KeyDownValue[2] == 1 and KeyDownValue[4] == 1)then
		rotation = 135;
	end
	
	if(KeyDownValue[1] == 1 and KeyDownValue[3] == 1)then
		rotation = 315;
	end
	
	if(KeyDownValue[2] == 1 and KeyDownValue[3] == 1)then
		rotation = 45;
	end
	
	
	
	if(keydowning)then
		MainCharacter:setRotate( MainCharacter:getRotateX() ,MainCharacter:getRotateY() ,rotation);
	end
	
	
	
	


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




function KeyDown(Lua_key)

	if(MainCharacter~= nil) then
		if( Lua_key == 87) then
			KeyDownValue[1] = 1;
			--MainCharacter:setRotate( MainCharacter:getRotateX() ,MainCharacter:getRotateY() ,270);
		end
		if( Lua_key == 83) then
			KeyDownValue[2] = 1;
			--MainCharacter:setRotate( MainCharacter:getRotateX() ,MainCharacter:getRotateY() ,90);
		end
		if( Lua_key == 65) then
			KeyDownValue[3] = 1;
			--MainCharacter:setRotate( MainCharacter:getRotateX() ,MainCharacter:getRotateY() ,360);
		end
		if( Lua_key == 68) then
			KeyDownValue[4] = 1;
			--MainCharacter:setRotate( MainCharacter:getRotateX() ,MainCharacter:getRotateY() ,180);
		end
	end
	return Lua_key;
end

function KeyUp(Lua_key)
	if(MainCharacter~= nil) then
		if( Lua_key == 87) then
			KeyDownValue[1] = 0;
		end
		if( Lua_key == 83) then
			KeyDownValue[2] = 0;
		end
		if( Lua_key == 65) then
			KeyDownValue[3] = 0;
		end
		if( Lua_key == 68) then
			KeyDownValue[4] = 0;
		end
	end
	return Lua_key;
end

function specialKeyPress(Lua_key)
end

function specialKeyUp(Lua_key)
end

function mouseMotion(lua_x,lua_y)
end