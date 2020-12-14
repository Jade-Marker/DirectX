camera = {}
initialPos = {}

cMoveSpeed = 10
cBoostScale = 4
cRotSpeed = 0.001
cCrouchAmount = 3

function Move(Position, Rotation, isForward, deltaTime, isBoosted)
	scalar = 0;

	if(isForward) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	Position.x = Position.x - scalar * math.cos(Rotation.y + math.pi/2) * cMoveSpeed * deltaTime
	Position.z = Position.z + scalar * math.sin(Rotation.y + math.pi/2) * cMoveSpeed * deltaTime
end

function MoveSide(Position, Rotation, isLeft, deltaTime, isBoosted)
	scalar = 0;

	if(isLeft) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	Position.x = Position.x - scalar * math.cos(Rotation.y) * cMoveSpeed * deltaTime
	Position.z = Position.z + scalar * math.sin(Rotation.y) * cMoveSpeed * deltaTime
end

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
	initialPos = InitialTransform.Position
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_5)) then
		SetMainCamera(camera)
	end

	if(GetMainCamera() == camera) then
		Position = Transform.Position
		Rotation = Transform.Rotation
		deltaX, deltaY = GetDeltaMousePos()
		isBoosted = GetKey(Input.KEY_SHIFT)


		if(GetKey(Input.KEY_W)) then
			Move(Position, Rotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_S)) then
			Move(Position, Rotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_A)) then
			MoveSide(Position, Rotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_D)) then
			MoveSide(Position, Rotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_CONTROL)) then
			Position.y = initialPos.y - cCrouchAmount
		else
			Position.y = initialPos.y	
		end

		Rotation.x = Rotation.x + deltaY * cRotSpeed
		Rotation.y = Rotation.y + deltaX * cRotSpeed
	end
end