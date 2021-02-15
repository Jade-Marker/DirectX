cMoveSpeed = 10
cBoostScale = 4
cRotSpeed = 1.25

function Move(EulerRotation, isForward, deltaTime, isBoosted)
	if(isForward) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	scalar = scalar * cMoveSpeed * deltaTime

	sinAngle = math.sin(-EulerRotation.y)
	cosAngle = math.cos(-EulerRotation.y)
	parent:GetParent():GetTransform():Translate(Vector3D(scalar * cosAngle, 0, -scalar * sinAngle))
end

function Update(deltaTime)
	isActive = GetEntityComponent(this, parent:GetParent(), ComponentType.CUSTOM_COMPONENT):GetFunction("IsActive")()

	if(isActive) then
		EulerRotation = Transform.Rotation:ToEuler()

		isBoosted = GetKey(Input.KEY_SHIFT)

		if(GetKey(Input.KEY_W)) then
			Move(EulerRotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_S)) then
			Move(EulerRotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_A)) then
			Transform:Rotate(Vector3D(0, cRotSpeed * deltaTime, 0))
		end

		if(GetKey(Input.KEY_D)) then
			Transform:Rotate(Vector3D(0, -cRotSpeed * deltaTime, 0))
		end
	end
end