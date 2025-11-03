// Made by Alexander Robinson. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AngelscriptProjectEditorTarget : TargetRules
{
	public AngelscriptProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "AngelscriptProject" } );
	}
}
